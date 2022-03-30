//
// Namespace for collecting tools used in TrkDiag tree filling
// Original author: A. Edmonds (November 2018)
//
#include "TrkAna/inc/InfoStructHelper.hh"
#include "Offline/RecoDataProducts/inc/TrkStrawHitSeed.hh"
#include "KinKal/Trajectory/CentralHelix.hh"
#include "Offline/TrackerGeom/inc/Tracker.hh"
#include <cmath>

namespace mu2e {
  void InfoStructHelper::fillHitCount(StrawHitFlagCollection const& shfC, HitCount& hitcount) {
    hitcount._nsd = shfC.size();
    for(const auto& shf : shfC) {
      if(shf.hasAllProperties(StrawHitFlag::energysel))++hitcount._nesel;
      if(shf.hasAllProperties(StrawHitFlag::radsel))++hitcount._nrsel;
      if(shf.hasAllProperties(StrawHitFlag::timesel))++hitcount._ntsel;
      if(shf.hasAllProperties(StrawHitFlag::bkg))++hitcount._nbkg;
      if(shf.hasAllProperties(StrawHitFlag::trksel))++hitcount._ntpk;
    }
  }

  void InfoStructHelper::fillHitCount(RecoCount const& nrec, HitCount& hitcount) {
    hitcount._nsd = nrec._nstrawdigi;
    hitcount._ncd = nrec._ncalodigi;
    hitcount._ncrvd = nrec._ncrvdigi;
    hitcount._nesel = nrec._nshfesel;
    hitcount._nrsel = nrec._nshfrsel;
    hitcount._ntsel = nrec._nshftsel;
    hitcount._nbkg = nrec._nshfbkg;
    hitcount._ntpk = nrec._nshftpk;
  }

  void InfoStructHelper::fillTrkInfo(const KalSeed& kseed,TrkInfo& trkinfo) {
    if(kseed.status().hasAllProperties(TrkFitFlag::kalmanConverged))
      trkinfo.status = 1;
    else if(kseed.status().hasAllProperties(TrkFitFlag::kalmanOK))
      trkinfo.status = 2;
    else
      trkinfo.status = -1;
    if(kseed.status().hasAllProperties(TrkFitFlag::CPRHelix))
      trkinfo.alg = 1;
    else if(kseed.status().hasAllProperties(TrkFitFlag::TPRHelix))
      trkinfo.alg = 0;
    else
      trkinfo.alg = -1;

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

    // Loop through the KalSegments
    double firstflt = 9999999;
    double lastflt = -9999999;
    for (const auto& kseg : kseed.segments()) {
      //	std::cout << "AE: min = " << kseg.fmin() << ", max = " << kseg.fmax() << std::endl;
      if (kseg.globalFlt(kseg.fmin()) < firstflt) {
        firstflt = kseg.globalFlt(kseg.fmin());
      }
      if (kseg.globalFlt(kseg.fmax()) > lastflt) {
        lastflt = kseg.globalFlt(kseg.fmax());
      }
    }
    trkinfo.startvalid = firstflt;
    trkinfo.endvalid = lastflt;

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
    trkinfo.nhits = 0; trkinfo.nactive = 0; trkinfo.ndouble = 0; trkinfo.ndactive = 0; trkinfo.nnullambig = 0;
    static StrawHitFlag active(StrawHitFlag::active);
    for (auto ihit = kseed.hits().begin(); ihit != kseed.hits().end(); ++ihit) {
      ++trkinfo.nhits;
      if (ihit->flag().hasAllProperties(active)) {
        ++trkinfo.nactive;
        if (ihit->ambig()==0) {
          ++trkinfo.nnullambig;
        }
      }
      auto jhit = ihit; jhit++;
      if(jhit != kseed.hits().end() && ihit->strawId().uniquePanel() ==
          jhit->strawId().uniquePanel()){
        ++trkinfo.ndouble;
        if(ihit->flag().hasAllProperties(active)) { ++trkinfo.ndactive; }
      }
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

      tshinfo._active = ihit->flag().hasAllProperties(active);
      tshinfo._plane = ihit->strawId().plane();
      tshinfo._panel = ihit->strawId().panel();
      tshinfo._layer = ihit->strawId().layer();
      tshinfo._straw = ihit->strawId().straw();

      // find nearest segment
      auto ikseg = kseed.nearestSegment(ihit->trkLen());
      if(ikseg != kseed.segments().end()){
        XYZVectorF dir;
        ikseg->helix().direction(ikseg->localFlt(ihit->trkLen()),dir);
        auto tdir = GenVector::Hep3Vec(dir);
        tshinfo._wdot = tdir.dot(straw.getDirection());
      }
      tshinfo._residerr = ihit->radialErr();
      // note; the following is the BIASED residual FIXME!
      tshinfo._resid = ihit->wireDOCA() -ihit->driftRadius()*ihit->ambig();
      tshinfo._rdrift = ihit->driftRadius();
      tshinfo._rdrifterr = ihit->radialErr();

      double rstraw = tracker.strawOuterRadius();
      tshinfo._dx = std::sqrt(std::max(0.0,rstraw*rstraw-tshinfo._rdrift*tshinfo._rdrift));

      tshinfo._trklen = ihit->trkLen();
      tshinfo._hlen = ihit->hitLen();
      tshinfo._t0 = ihit->t0().t0();
      tshinfo._t0err = ihit->t0().t0Err();
      tshinfo._ht = ihit->hitTime();
      tshinfo._ambig = ihit->ambig();
      tshinfo._doca = ihit->wireDOCA();
      tshinfo._edep = ihit->energyDep();
      tshinfo._wdist = ihit->wireDist();
      tshinfo._werr = ihit->wireRes();
      tshinfo._driftend = ihit->driftEnd();
      tshinfo._tdrift = ihit->hitTime() - ihit->signalTime() - ihit->t0().t0();
      auto const& wiredir = straw.getDirection();
      auto const& mid = straw.getMidPoint();
      CLHEP::Hep3Vector hpos = mid + wiredir*ihit->hitLen();
      tshinfo._poca = XYZVectorF(hpos);

      // count correlations with other TSH
      for(std::vector<TrkStrawHitSeed>::const_iterator jhit=kseed.hits().begin(); jhit != ihit; ++jhit) {
        if(tshinfo._plane ==  jhit->strawId().plane() &&
            tshinfo._panel == jhit->strawId().panel() ){
          tshinfo._dhit = true;
          if (jhit->flag().hasAllProperties(active)) {
            tshinfo._dactive = true;
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

      tminfo._plane = i_straw.straw().getPlane();
      tminfo._panel = i_straw.straw().getPanel();
      tminfo._layer = i_straw.straw().getLayer();
      tminfo._straw = i_straw.straw().getStraw();

      tminfo._active = i_straw.active();
      tminfo._dp = i_straw.pfrac();
      tminfo._radlen = i_straw.radLen();
      tminfo._doca = i_straw.doca();
      tminfo._tlen = i_straw.trkLen();

      tminfos.push_back(tminfo);
    }
  }

  void InfoStructHelper::fillCaloHitInfo(const KalSeed& kseed, TrkCaloHitInfo& tchinfo) {
    if (kseed.hasCaloCluster()) {
      auto const& tch = kseed.caloHit();
      auto const& cc = tch.caloCluster();

      tchinfo.active = tch.flag().hasAllProperties(StrawHitFlag::active);
      tchinfo.did = cc->diskID();
      tchinfo.trklen = tch.trkLen();
      tchinfo.clen = tch.hitLen();

      if(tch.flag().hasAllProperties(StrawHitFlag::doca)) {
        tchinfo.doca = tch.clusterAxisDOCA();
      }
      else {
        tchinfo.doca = -100.0;
      }
      // add the propagation time offsetA
      tchinfo.t0 = tch.t0().t0();
      tchinfo.t0err = tch.t0().t0Err();
      tchinfo.ct = tch.time(); // time used to constrain T0 by this hit: includes the 'propagation time' offset
      tchinfo.cterr = tch.timeErr();
      tchinfo.edep = cc->energyDep();
      // transform cog to tracker coordinates; requires 2 steps.  This is at the front
      // of the disk
      mu2e::GeomHandle<mu2e::Calorimeter> calo;
      XYZVectorF cpos = XYZVectorF(calo->geomUtil().mu2eToTracker(calo->geomUtil().diskToMu2e(cc->diskID(),cc->cog3Vector())));
      // move to the front face and
      // add the cluster length (relative to the front face).  crystal size should come from geom FIXME!
      cpos.SetZ(cpos.z() -200.0 + tch.hitLen());
      tchinfo.poca = cpos;
      // find the nearest segment
      auto ikseg = kseed.nearestSegment(tch.trkLen());
      if(ikseg != kseed.segments().end()){
        ikseg->mom(ikseg->localFlt(tch.trkLen()),tchinfo.mom);
      }
    }
  }

  void InfoStructHelper::fillTrkQualInfo(const TrkQual& tqual, TrkQualInfo& trkqualInfo) {
    int n_trkqual_vars = TrkQual::n_vars;
    for (int i_trkqual_var = 0; i_trkqual_var < n_trkqual_vars; ++i_trkqual_var) {
      TrkQual::MVA_varindex i_index = TrkQual::MVA_varindex(i_trkqual_var);
      trkqualInfo._trkqualvars[i_trkqual_var] = tqual[i_index];
    }
    trkqualInfo._mvaout = tqual.MVAOutput();
    trkqualInfo._mvastat = tqual.status();
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
