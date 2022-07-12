//
// Namespace for collecting tools used in TrkDiag tree filling
// Original author: A. Edmonds (November 2018)
//
#include "TrkAna/inc/InfoStructHelper.hh"
#include "Offline/RecoDataProducts/inc/TrkStrawHitSeed.hh"
#include "KinKal/Trajectory/CentralHelix.hh"
#include "Offline/TrackerGeom/inc/Tracker.hh"
#include "Offline/Mu2eKinKal/inc/WireHitState.hh"
#include <cmath>

namespace mu2e {
  void InfoStructHelper::fillHitCount(StrawHitFlagCollection const& shfC, HitCount& hitcount) {
    hitcount.nsd = shfC.size();
    for(const auto& shf : shfC) {
      if(shf.hasAllProperties(StrawHitFlag::energysel))++hitcount.nesel;
      if(shf.hasAllProperties(StrawHitFlag::radsel))++hitcount.nrsel;
      if(shf.hasAllProperties(StrawHitFlag::timesel))++hitcount.ntsel;
      if(shf.hasAllProperties(StrawHitFlag::bkg))++hitcount.nbkg;
      if(shf.hasAllProperties(StrawHitFlag::trksel))++hitcount.ntpk;
    }
  }

  void InfoStructHelper::fillHitCount(RecoCount const& nrec, HitCount& hitcount) {
    hitcount.nsd = nrec._nstrawdigi;
    hitcount.ncd = nrec._ncalodigi;
    hitcount.ncrvd = nrec._ncrvdigi;
    hitcount.nesel = nrec._nshfesel;
    hitcount.nrsel = nrec._nshfrsel;
    hitcount.ntsel = nrec._nshftsel;
    hitcount.nbkg = nrec._nshfbkg;
    hitcount.ntpk = nrec._nshftpk;
  }

  void InfoStructHelper::fillTrkInfo(const KalSeed& kseed,TrkInfo& trkinfo) {
    if(kseed.status().hasAllProperties(TrkFitFlag::kalmanConverged))
      trkinfo.status = 1;
    else if(kseed.status().hasAllProperties(TrkFitFlag::kalmanOK))
      trkinfo.status = 2;
    else
      trkinfo.status = -1;

    if(kseed.status().hasAllProperties(TrkFitFlag::FitOK)){
      trkinfo.goodfit = 1;
    } else
      trkinfo.goodfit = 0;

    if(kseed.status().hasAllProperties(TrkFitFlag::CPRHelix))
      trkinfo.seedalg = 1;
    else if(kseed.status().hasAllProperties(TrkFitFlag::TPRHelix))
      trkinfo.seedalg = 0;

    if(kseed.status().hasAllProperties(TrkFitFlag::KKLoopHelix))
      trkinfo.fitalg =1;
    else if(kseed.status().hasAllProperties(TrkFitFlag::KKCentralHelix))
      trkinfo.fitalg = 2;
    else if(kseed.status().hasAllProperties(TrkFitFlag::KKLine))
      trkinfo.fitalg = 3;
    else
      trkinfo.fitalg = 0;

    trkinfo.pdg = kseed.particle();
    trkinfo.t0 = kseed.t0().t0();
    trkinfo.t0err = kseed.t0().t0Err();

    fillTrkInfoHits(kseed, trkinfo);

    trkinfo.chisq = kseed.chisquared();
    trkinfo.fitcon = kseed.fitConsistency();
    trkinfo.nseg = kseed.nTrajSegments();

    for(std::vector<TrkStrawHitSeed>::const_iterator ihit=kseed.hits().begin(); ihit != kseed.hits().end(); ++ihit) {
      if(ihit->flag().hasAllProperties(StrawHitFlag::active)) {
        trkinfo.firstflt = ihit->trkLen();
        break;
      }
    }
    for(std::vector<TrkStrawHitSeed>::const_reverse_iterator ihit=kseed.hits().rbegin(); ihit != kseed.hits().rend(); ++ihit) {
      if(ihit->flag().hasAllProperties(StrawHitFlag::active)) {
        trkinfo.lastflt = ihit->trkLen();
        break;
      }
    }

    // Legacy data: 'flight range'
    trkinfo.startvalid = kseed.segments().front().tmin();
    trkinfo.endvalid = kseed.segments().back().tmax();

    fillTrkInfoStraws(kseed, trkinfo);
  }

  void InfoStructHelper::fillTrkFitInfo(const KalSeed& kseed,TrkFitInfo& trkfitinfo, const XYZVectorF& pos) {
    const auto& ksegIter = kseed.nearestSegment(pos);
    if (ksegIter == kseed.segments().end()) {
      cet::exception("InfoStructHelper") << "Couldn't find KalSegment that includes pos = " << pos;
    }
    trkfitinfo.mom = ksegIter->momentum3();
    trkfitinfo.pos = ksegIter->position3();
    trkfitinfo.momerr = ksegIter->momerr();
    trkfitinfo.d0 = ksegIter->centralHelix().d0();
    trkfitinfo.maxr = ksegIter->centralHelix().d0() + 2.0/ksegIter->centralHelix().omega();
    trkfitinfo.td = ksegIter->centralHelix().tanDip();
  }

  void InfoStructHelper::fillTrkInfoHits(const KalSeed& kseed, TrkInfo& trkinfo) {
    trkinfo.nhits = trkinfo.nactive = trkinfo.ndouble = trkinfo.ndactive = trkinfo.nplanes = trkinfo.planespan = trkinfo.nnullambig = 0;
    static StrawHitFlag active(StrawHitFlag::active);
    std::set<unsigned> planes;
    uint16_t minplane(0), maxplane(0);
    for (auto ihit = kseed.hits().begin(); ihit != kseed.hits().end(); ++ihit) {
      ++trkinfo.nhits;
      if (ihit->strawHitState()>WireHitState::inactive) {
        ++trkinfo.nactive;
        planes.insert(ihit->strawId().plane());
        minplane = std::min(minplane, ihit->strawId().plane());
        maxplane = std::max(maxplane, ihit->strawId().plane());
        if (ihit->strawHitState()==WireHitState::null) {
          ++trkinfo.nnullambig;
        }
        auto jhit = ihit; jhit++;
        if(jhit != kseed.hits().end() && ihit->strawId().uniquePanel() == jhit->strawId().uniquePanel()){
          ++trkinfo.ndouble;
          if(jhit->strawHitState()>WireHitState::inactive) { ++trkinfo.ndactive; }
        }
      }
      trkinfo.nplanes = planes.size();
      trkinfo.planespan = abs(maxplane-minplane);
    }

    trkinfo.ndof = trkinfo.nactive -5; // this won't work with KinKal fits FIXME
    if (kseed.hasCaloCluster()) {
      ++trkinfo.ndof;
    }
  }

  void InfoStructHelper::fillTrkInfoStraws(const KalSeed& kseed, TrkInfo& trkinfo) {
    trkinfo.nmat = 0; trkinfo.nmatactive = 0; trkinfo.radlen = 0.0;
    for (std::vector<TrkStraw>::const_iterator i_straw = kseed.straws().begin(); i_straw != kseed.straws().end(); ++i_straw) {
      ++trkinfo.nmat;
      if (i_straw->active()) {
        ++trkinfo.nmatactive;
        trkinfo.radlen += i_straw->radLen();
      }
    }
  }

  void InfoStructHelper::fillHitInfo(const KalSeed& kseed, std::vector<TrkStrawHitInfo>& tshinfos ) {
    tshinfos.clear();
    // loop over hits

    static StrawHitFlag active(StrawHitFlag::active);
    const Tracker& tracker = *GeomHandle<Tracker>();
    for(std::vector<TrkStrawHitSeed>::const_iterator ihit=kseed.hits().begin(); ihit != kseed.hits().end(); ++ihit) {
      TrkStrawHitInfo tshinfo;
      auto const& straw = tracker.getStraw(ihit->strawId());

      tshinfo.state = ihit->_ambig;
      tshinfo.algo = ihit->_algo;
      tshinfo.driftend   = ihit->_end.end();
      tshinfo.plane = ihit->strawId().plane();
      tshinfo.panel = ihit->strawId().panel();
      tshinfo.layer = ihit->strawId().layer();
      tshinfo.straw = ihit->strawId().straw();

      tshinfo.edep   = ihit->_edep;
      tshinfo.htime   = ihit->_htime;
      tshinfo.wdist   = ihit->_wdist;
      tshinfo.werr   = ihit->_werr;
      tshinfo.ptoca   = ihit->_ptoca;
      tshinfo.wdoca   = ihit->_wdoca;
      tshinfo.wdocavar   = ihit->_wdocavar;
      tshinfo.wdt   = ihit->_wdt;
      tshinfo.wtocavar   = ihit->_wtocavar;
      tshinfo.doca   = ihit->_doca;
      tshinfo.docavar   = ihit->_docavar;
      tshinfo.dt   = ihit->_dt;
      tshinfo.tocavar   = ihit->_tocavar;
      tshinfo.upos   = ihit->_upos;
      tshinfo.tresid   = ihit->_tresid;
      tshinfo.tresidmvar   = ihit->_tresidmvar;
      tshinfo.tresidpvar   = ihit->_tresidpvar;
      tshinfo.dresid   = ihit->_dresid;
      tshinfo.dresidmvar   = ihit->_dresidmvar;
      tshinfo.dresidpvar   = ihit->_dresidpvar;

      // find nearest segment
      auto ikseg = kseed.nearestSegment(ihit->_ptoca);
      if(ikseg != kseed.segments().end()){
        XYZVectorF dir;
        ikseg->helix().direction(ikseg->localFlt(ihit->trkLen()),dir);
        auto tdir = GenVector::Hep3Vec(dir);
        tshinfo.wdot = tdir.dot(straw.getDirection());
      }
      auto const& wiredir = straw.getDirection();
      auto const& mid = straw.getMidPoint();
      CLHEP::Hep3Vector hpos = mid + wiredir*ihit->hitLen();
      tshinfo.poca = XYZVectorF(hpos);

      // count correlations with other TSH
      // OBSOLETE: replace this with a test for KinKal StrawHitClusters
      for(std::vector<TrkStrawHitSeed>::const_iterator jhit=kseed.hits().begin(); jhit != kseed.hits().end(); ++jhit) {
        if(jhit != ihit && ihit->strawId().plane() ==  jhit->strawId().plane() &&
            ihit->strawId().panel() == jhit->strawId().panel() ){
          tshinfo.dhit = true;
          if (jhit->flag().hasAllProperties(active)) {
            tshinfo.dactive = true;
            break;
          }
        }
      }
      tshinfos.push_back(tshinfo);
    }
  }

  void InfoStructHelper::fillMatInfo(const KalSeed& kseed, std::vector<TrkStrawMatInfo>& tminfos ) {
    tminfos.clear();
    // loop over sites, pick out the materials

    for(const auto& i_straw : kseed.straws()) {
      TrkStrawMatInfo tminfo;

      tminfo.plane = i_straw.straw().getPlane();
      tminfo.panel = i_straw.straw().getPanel();
      tminfo.layer = i_straw.straw().getLayer();
      tminfo.straw = i_straw.straw().getStraw();

      tminfo.active = i_straw.active();
      tminfo.dp = i_straw.pfrac();
      tminfo.radlen = i_straw.radLen();
      tminfo.doca = i_straw.doca();
      tminfo.tlen = i_straw.trkLen();

      tminfos.push_back(tminfo);
    }
  }

  void InfoStructHelper::fillCaloHitInfo(const KalSeed& kseed, TrkCaloHitInfo& tchinfo) {
    if (kseed.hasCaloCluster()) {
      auto const& tch = kseed.caloHit();
      auto const& cc = tch.caloCluster();

      tchinfo.active = tch.flag().hasAllProperties(StrawHitFlag::active);
      tchinfo.did = cc->diskID();
      tchinfo.poca = tch.clusterPosition();
      tchinfo.mom = tch.trackMomentum();
      tchinfo.cdepth = tch.clusterDepth();
      tchinfo.doca = tch.clusterAxisDOCA();
      tchinfo.dt = tch.clusterAxisPOCADeltaT();
      tchinfo.toca = tch.clusterAxisTOCA();
      tchinfo.tocavar = tch.clusterAxisTOCAVar();
      tchinfo.tresid   = tch._tresid;
      tchinfo.tresidmvar   = tch._tresidmvar;
      tchinfo.tresidpvar   = tch._tresidpvar;
      tchinfo.edep = cc->energyDep();
    }
  }

  void InfoStructHelper::fillTrkQualInfo(const TrkQual& tqual, TrkQualInfo& trkqualInfo) {
    int n_trkqual_vars = TrkQual::n_vars;
    for (int i_trkqual_var = 0; i_trkqual_var < n_trkqual_vars; ++i_trkqual_var) {
      TrkQual::MVA_varindex i_index = TrkQual::MVA_varindex(i_trkqual_var);
      trkqualInfo.trkqualvars[i_trkqual_var] = tqual[i_index];
    }
    trkqualInfo.mvaout = tqual.MVAOutput();
    trkqualInfo.mvastat = tqual.status();
  }


  void InfoStructHelper::fillHelixInfo(art::Ptr<HelixSeed> const& hptr, HelixInfo& hinfo) {
    if(hptr.isNonnull()){
      // count hits, active and not
      for(size_t ihit=0;ihit < hptr->hits().size(); ihit++){
        auto const& hh = hptr->hits()[ihit];
        hinfo.nch++;
        hinfo.nsh += hh.nStrawHits();
        if(!hh.flag().hasAnyProperty(StrawHitFlag::outlier)){
          hinfo.ncha++;
          hinfo.nsha += hh.nStrawHits();
        }
        if( hptr->status().hasAllProperties(TrkFitFlag::TPRHelix))
          hinfo.flag = 1;
        else if( hptr->status().hasAllProperties(TrkFitFlag::CPRHelix))
          hinfo.flag = 2;
        hinfo.t0err = hptr->t0().t0Err();
        hinfo.mom = 0.299792*hptr->helix().momentum()*_bz0; //FIXME!
        hinfo.chi2xy = hptr->helix().chi2dXY();
        hinfo.chi2fz = hptr->helix().chi2dZPhi();
        if(hptr->caloCluster().isNonnull())
          hinfo.ecalo  = hptr->caloCluster()->energyDep();
      }
    }
  }

  void InfoStructHelper::fillTrkPIDInfo(const TrkCaloHitPID& tchp, const KalSeed& kseed, TrkPIDInfo& trkpidInfo) {
    mu2e::GeomHandle<mu2e::Calorimeter> calo;
    int n_trktchpid_vars = TrkCaloHitPID::n_vars;
    for (int i_trktchpid_var = 0; i_trktchpid_var < n_trktchpid_vars; ++i_trktchpid_var) {
      TrkCaloHitPID::MVA_varindex i_index = TrkCaloHitPID::MVA_varindex(i_trktchpid_var);
      trkpidInfo._tchpvars[i_trktchpid_var] = (float) tchp[i_index];
    }
    trkpidInfo._mvaout = tchp.MVAOutput();
    trkpidInfo._mvastat = tchp.status();
    // extrapolate the track to the calorimeter disk faces and record the transverse radius
    // Use the last segment
    auto const& trkhel = kseed.segments().back().helix();
    static const CLHEP::Hep3Vector origin;
    for(int idisk=0;idisk < 2; idisk++){
      auto ffpos = calo->geomUtil().mu2eToTracker(calo->geomUtil().diskFFToMu2e(idisk,origin));
      float flen = trkhel.zFlight(ffpos.z());
      float blen = trkhel.zFlight(ffpos.z()+207.5); // private communication B. Echenard FIXME!!!!
      XYZVectorF extpos;
      trkhel.position(flen,extpos);
      trkpidInfo._diskfrad[idisk] = sqrt(extpos.Perp2());
      trkhel.position(blen,extpos);
      trkpidInfo._diskbrad[idisk] = sqrt(extpos.Perp2());
    }
  }

  void InfoStructHelper::fillCrvHitInfo(art::Ptr<CrvCoincidenceCluster> const& crvCoinc, CrvHitInfoReco& crvHitInfo) {
    crvHitInfo._crvSectorType = crvCoinc->GetCrvSectorType();
    crvHitInfo._x = crvCoinc->GetAvgCounterPos().x();
    crvHitInfo._y = crvCoinc->GetAvgCounterPos().y();
    crvHitInfo._z = crvCoinc->GetAvgCounterPos().z();
    crvHitInfo._timeWindowStart = crvCoinc->GetStartTime();
    crvHitInfo._timeWindowEnd = crvCoinc->GetEndTime();
    crvHitInfo._PEs = crvCoinc->GetPEs();
    crvHitInfo._nCoincidenceHits = crvCoinc->GetCrvRecoPulses().size();
  }
}
