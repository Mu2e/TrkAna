//
// Namespace for collecting tools used in MC truth evaluation
// Original author: Dave Brown (LBNL) 8/10/2016
//
#include "TrkAna/inc/InfoMCStructHelper.hh"
#include "Offline/MCDataProducts/inc/StepPointMC.hh"
#include "Offline/MCDataProducts/inc/SimParticle.hh"
#include "Offline/MCDataProducts/inc/MCRelationship.hh"

#include "Offline/TrackerGeom/inc/Tracker.hh"
#include "Offline/Mu2eUtilities/inc/TwoLinePCA.hh"
#include "Offline/DataProducts/inc/EventWindowMarker.hh"

#include "Offline/GlobalConstantsService/inc/GlobalConstantsHandle.hh"
#include "Offline/GlobalConstantsService/inc/ParticleDataList.hh"
#include "Offline/GeometryService/inc/GeomHandle.hh"
#include "Offline/GeometryService/inc/DetectorSystem.hh"
#include "Offline/ConditionsService/inc/ConditionsHandle.hh"
#include "Offline/ConditionsService/inc/AcceleratorParams.hh"
#include "art/Framework/Principal/Handle.h"

#include <map>
#include <limits>

namespace mu2e {

  void InfoMCStructHelper::updateEvent(const art::Event& event) {
    event.getByLabel(_spctag,_spcH);
    ConditionsHandle<AcceleratorParams> accPar("ignored");
    _mbtime = accPar->deBuncherPeriod;
    art::Handle<EventWindowMarker> ewMarkerHandle;
    event.getByLabel(_ewMarkerTag, ewMarkerHandle);
    const EventWindowMarker& ewMarker(*ewMarkerHandle);
    _onSpill = (ewMarker.spillType() == EventWindowMarker::SpillType::onspill);
  }

  void InfoMCStructHelper::fillTrkInfoMC(const KalSeed& kseed, const KalSeedMC& kseedmc, TrkInfoMC& trkinfomc) {
    // use the primary match of the track
    // primary associated SimParticle
    auto trkprimary = kseedmc.simParticle().simParticle(_spcH);
    if(kseedmc.simParticles().size() > 0){
      auto const& simp = kseedmc.simParticles().front();
      trkinfomc.valid = true;
      trkinfomc.gen = simp._gid.id();
      trkinfomc.pdg = simp._pdg;
      trkinfomc.proc = simp._proc;
      trkinfomc.nhits = simp._nhits; // number of hits from the primary particle
      trkinfomc.nactive = simp._nactive; // number of active hits from the primary particle
      trkinfomc.prel = simp._rel; // relationship of the track primary to the event primary
    }

    fillTrkInfoMCDigis(kseed, kseedmc, trkinfomc);

    // fill the origin information of this SimParticle
    GeomHandle<DetectorSystem> det;
    trkinfomc.otime = trkprimary->startGlobalTime();
    trkinfomc.opos = XYZVectorF(det->toDetector(trkprimary->startPosition()));
    trkinfomc.omom = XYZVectorF(trkprimary->startMomentum().vect());
  }

  void InfoMCStructHelper::fillTrkInfoMCDigis(const KalSeed& kseed, const KalSeedMC& kseedmc, TrkInfoMC& trkinfomc) {
    trkinfomc.ndigi = 0; trkinfomc.ndigigood = 0, trkinfomc.nambig = 0;
    // find the first segment momentum as reference
    double simmom = 1.0;
    if(kseedmc.simParticles().size()>0)
      simmom = sqrt(kseedmc.simParticles().front()._mom.mag2());
    for(size_t i_digi = 0; i_digi < kseedmc._tshmcs.size(); ++i_digi) {
      const auto& tshmc = kseedmc._tshmcs.at(i_digi);

      if (kseedmc.simParticle(tshmc._spindex)._rel == MCRelationship::same) {
        ++trkinfomc.ndigi;
        if(sqrt(tshmc.particleMomentum().mag2())/simmom > _mingood) {
          ++trkinfomc.ndigigood;
        }

        // easiest way to get MC ambiguity is through info object
        TrkStrawHitInfoMC tshinfomc;
        fillHitInfoMC(kseedmc,tshinfomc,tshmc);
        // the MCDigi list can be longer than the # of TrkStrawHits in the seed:
        if(i_digi < kseed.hits().size()){
          const auto& ihit = kseed.hits().at(i_digi);
          if(ihit.flag().hasAllProperties(StrawHitFlag::active) && ihit.ambig()*tshinfomc.ambig > 0) {
            ++trkinfomc.nambig;
          }
        }
      }
    }
  }

  void InfoMCStructHelper::fillHitInfoMC(const KalSeedMC& kseedmc, TrkStrawHitInfoMC& tshinfomc, const TrkStrawHitMC& tshmc) {
    const Tracker& tracker = *GeomHandle<Tracker>();

    const SimPartStub& simPart = kseedmc.simParticle(tshmc._spindex);
    tshinfomc.pdg = simPart._pdg;
    tshinfomc.proc = simPart._proc;
    tshinfomc.gen = simPart._gid.id();
    tshinfomc.rel = simPart._rel;
    tshinfomc.earlyend = tshmc._earlyend._end;
    tshinfomc.t0 = tshmc._time;
    tshinfomc.tdrift = tshmc._tdrift;
    tshinfomc.rdrift = tshmc._rdrift;
    tshinfomc.tprop = tshmc._tprop;
    tshinfomc.edep = tshmc._energySum;
    tshinfomc.mom = std::sqrt(tshmc._mom.mag2());
    tshinfomc.cpos  = tshmc._cpos;

    // find the step midpoint
    const Straw& straw = tracker.getStraw(tshmc._strawId);
    auto mcsep = tshmc._cpos-XYZVectorF(straw.getMidPoint());
    auto wdir = XYZVectorF(straw.getDirection());
    tshinfomc.len = mcsep.Dot(wdir);
    auto mdir = tshmc._mom.Unit();
    auto mcperp = mdir.Cross(wdir).Unit();
    double dperp = mcperp.Dot(mcsep);
    tshinfomc.twdot = mdir.Dot(wdir);
    tshinfomc.dist = fabs(dperp);
    auto wperp = wdir.Cross(mcperp);
    tshinfomc.tau = mcsep.Dot(wperp);
    tshinfomc.cdist = sqrt(tshinfomc.dist*tshinfomc.dist+tshinfomc.tau*tshinfomc.tau);
    tshinfomc.ambig = dperp > 0 ? -1 : 1; // follow TrkPoca convention
    tshinfomc.doca = -1*dperp;
  }

  void InfoMCStructHelper::fillAllSimInfos(const KalSeedMC& kseedmc, std::vector<SimInfo>& siminfos, int n_generations) {
    auto trkprimary = kseedmc.simParticle().simParticle(_spcH)->originParticle();

    for (int i_generation = 0; i_generation < n_generations; ++i_generation) {
      fillSimInfo(trkprimary, siminfos.at(i_generation));
      if (trkprimary.parent().isNonnull()) {
        trkprimary = trkprimary.parent()->originParticle();
      }
      else {
        break; // this particle doesn't have a parent
      }
    }
  }

  void InfoMCStructHelper::fillPriInfo(const KalSeedMC& kseedmc, const PrimaryParticle& primary, SimInfo& priinfo) {
    auto trkprimary = kseedmc.simParticle().simParticle(_spcH);

    // go through the SimParticles of this primary, and find the one most related to the
    // downstream fit (KalSeedMC)

    if (!primary.primarySimParticles().empty()) {
      auto bestprimarysp = primary.primarySimParticles().front();
      MCRelationship bestrel;
      for(auto const& spp : primary.primarySimParticles()){
        MCRelationship mcrel(spp,trkprimary);
        if(mcrel > bestrel){
          bestrel = mcrel;
          bestprimarysp = spp;
        }
      } // redundant: FIXME!
      fillSimInfo(bestprimarysp, priinfo);
    }
  }


  void InfoMCStructHelper::fillSimInfo(const art::Ptr<SimParticle>& sp, SimInfo& siminfo) {
    if(sp.isNonnull()){
      fillSimInfo(*sp, siminfo);
    }
    else {
      siminfo.valid = false;
    }
  }

  void InfoMCStructHelper::fillSimInfo(const SimParticle& sp, SimInfo& siminfo) {

    GeomHandle<DetectorSystem> det;

    siminfo.valid = true;
    siminfo.pdg = sp.pdgId();
    siminfo.gen = sp.creationCode();
    siminfo.time = sp.startGlobalTime();
    siminfo.mom = XYZVectorF(sp.startMomentum());
    siminfo.pos = XYZVectorF(det->toDetector(sp.startPosition()));
  }

  void InfoMCStructHelper::fillTrkInfoMCStep(const KalSeedMC& kseedmc, TrkInfoMCStep& trkinfomcstep,
      std::vector<VirtualDetectorId> const& vids, double target_time) {
    ConditionsHandle<AcceleratorParams> accPar("ignored");
    GeomHandle<DetectorSystem> det;
    GlobalConstantsHandle<ParticleDataList> pdt;
    static CLHEP::Hep3Vector vpoint_mu2e = det->toMu2e(CLHEP::Hep3Vector(0.0,0.0,0.0));

    const auto& mcsteps = kseedmc._vdsteps;
    double dmin = std::numeric_limits<double>::max();
    for (const auto& i_mcstep : mcsteps) {
      for(auto vid : vids) {
        if (i_mcstep._vdid == vid) {
          // take the VD step with the time closest to target_time
          // this is so that we can take the correct step when looking at upstream/downstream tracks
          // This won't work for extracted or OffSpill: FIXME!!!
          double corrected_time;
          if(_onSpill) {
            corrected_time = std::fmod(i_mcstep._time,_mbtime);
          } else {
            corrected_time = i_mcstep._time;
          }
          if(fabs(target_time - corrected_time) < dmin){
            dmin = fabs(target_time - corrected_time);//i_mcstep._time;
            trkinfomcstep.valid = true;
            trkinfomcstep.time = i_mcstep._time;
            trkinfomcstep.mom = XYZVectorF(i_mcstep._mom);
            trkinfomcstep.pos = XYZVectorF(i_mcstep._pos);
          }
        }
      }
    }
  }

  void InfoMCStructHelper::fillHitInfoMCs(const KalSeedMC& kseedmc, std::vector<TrkStrawHitInfoMC>& tshinfomcs) {
    tshinfomcs.clear();

    for(const auto& i_tshmc : kseedmc._tshmcs) {
      TrkStrawHitInfoMC tshinfomc;
      fillHitInfoMC(kseedmc, tshinfomc, i_tshmc);
      tshinfomcs.push_back(tshinfomc);
    }
  }

  void InfoMCStructHelper::fillCaloClusterInfoMC(CaloClusterMC const& ccmc, CaloClusterInfoMC& ccimc) {
    auto const& edeps = ccmc.energyDeposits();
    ccimc.nsim = edeps.size();
    ccimc.etot = ccmc.totalEnergyDep();
    if(ccmc.energyDeposits().size() > 0){
      auto const& primary = edeps.front();
      ccimc.eprimary = primary.energyDep();
      ccimc.tavg = primary.time(); // this is unnecessary FIXMI
      ccimc.tprimary = primary.time();
      ccimc.prel = primary.rel();
    }
  }

  void InfoMCStructHelper::fillCrvHitInfoMC(art::Ptr<CrvCoincidenceClusterMC> const& crvCoincMC, CrvHitInfoMC& crvHitInfoMC) {
    if(crvCoincMC->HasMCInfo()) {
      const art::Ptr<SimParticle> &simParticle = crvCoincMC->GetMostLikelySimParticle();
      art::Ptr<SimParticle> primaryParticle = simParticle;
      art::Ptr<SimParticle> parentParticle = simParticle;
      art::Ptr<SimParticle> gparentParticle = simParticle;
      int i_gen = 0;
      while (primaryParticle->hasParent()) {
        primaryParticle = primaryParticle->parent();
        if (i_gen ==0) {
          parentParticle = primaryParticle;
          gparentParticle = primaryParticle;
        }
        else if (i_gen == 1) {
          gparentParticle = primaryParticle;
        }
        ++i_gen;
      }
      crvHitInfoMC._valid = true;
      crvHitInfoMC._pdgId = simParticle->pdgId();
      crvHitInfoMC._primaryPdgId = primaryParticle->pdgId();
      crvHitInfoMC._primaryE = primaryParticle->startMomentum().e() - primaryParticle->startMomentum().m();
      crvHitInfoMC._primaryX = primaryParticle->startPosition().x();
      crvHitInfoMC._primaryY = primaryParticle->startPosition().y();
      crvHitInfoMC._primaryZ = primaryParticle->startPosition().z();
      crvHitInfoMC._parentPdgId = parentParticle->pdgId();
      crvHitInfoMC._parentE = parentParticle->startMomentum().e()  - parentParticle->startMomentum().m();
      crvHitInfoMC._parentX = parentParticle->startPosition().x();
      crvHitInfoMC._parentY = parentParticle->startPosition().y();
      crvHitInfoMC._parentZ = parentParticle->startPosition().z();
      crvHitInfoMC._gparentPdgId = gparentParticle->pdgId();
      crvHitInfoMC._gparentE = gparentParticle->startMomentum().e() - gparentParticle->startMomentum().m();
      crvHitInfoMC._gparentX = gparentParticle->startPosition().x();
      crvHitInfoMC._gparentY = gparentParticle->startPosition().y();
      crvHitInfoMC._gparentZ = gparentParticle->startPosition().z();
      crvHitInfoMC._x = crvCoincMC->GetEarliestHitPos().x();
      crvHitInfoMC._y = crvCoincMC->GetEarliestHitPos().y();
      crvHitInfoMC._z = crvCoincMC->GetEarliestHitPos().z();
      crvHitInfoMC._time = crvCoincMC->GetEarliestHitTime();
      crvHitInfoMC._depositedEnergy = crvCoincMC->GetTotalEnergyDeposited();
    }
  }

  void InfoMCStructHelper::fillExtraMCStepInfos(KalSeedMC const& kseedmc, StepPointMCCollection const& mcsteps,
      MCStepInfos& mcsic, MCStepSummaryInfo& mcssi) {
    GeomHandle<DetectorSystem> det;
    mcssi.reset();
    mcsic.clear();
    MCStepInfo mcsi;
    // only count the extra steps associated with the primary MC truth match
    auto simp = kseedmc.simParticle().simParticle(_spcH);
    //    std::cout << "KalSeedMC simp kep " << simp.key()
    //      << " start mom " << simp->startMomentum().vect()
    //      << " pos " << simp->startPosition() << std::endl;
    for(auto const& mcstep : mcsteps) {
      //     std::cout << "MCStep simp key " << mcstep.simParticle().key()
      //       << " start mom " << mcstep.simParticle()->startMomentum().vect()
      //       << " pos " << mcstep.simParticle()->startPosition() << std::endl;
      if(mcstep.simParticle().key() == simp.key()){
        // combine steps if they are in the same material.  They must be close in time too, since the particle may
        // re-enter the same material
        auto spos = XYZVectorF(det->toDetector(mcstep.position()));
        if(static_cast<int>(mcstep.volumeId()) == mcsi.vid && fabs(mcstep.time()-mcsi.time)<0.1 ){
          mcsi.de += mcstep.totalEDep();
          mcsi.dp += mcstep.postMomentum().mag() - mcstep.momentum().mag();
        } else {
          if(mcsi.valid()){
            // save this step
            mcsic.push_back(mcsi);
            // add its info to the summary
            mcssi.addStep(mcsi);
          }
          // initialize the new step
          mcsi.reset();
          mcsi.vid = mcstep.volumeId();
          mcsi.time = mcstep.time();
          mcsi.de = mcstep.totalEDep();
          mcsi.dp = mcstep.postMomentum().mag()- mcstep.momentum().mag();
          mcsi.mom = mcstep.momentum();
          mcsi.pos = spos;
        }
      }
    }
    // finalize the last step
    if(mcsi.valid()){
      mcsic.push_back(mcsi);
      mcssi.addStep(mcsi);
    }
  }
}
