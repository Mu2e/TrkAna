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
#include "BTrk/TrkBase/TrkHelixUtils.hh"

#include "Offline/GlobalConstantsService/inc/GlobalConstantsHandle.hh"
#include "Offline/GlobalConstantsService/inc/ParticleDataList.hh"
#include "Offline/GeometryService/inc/GeomHandle.hh"
#include "Offline/GeometryService/inc/DetectorSystem.hh"

#include <map>
#include <limits>

namespace mu2e {
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
    tshinfomc.t0 = tshmc._time;
    tshinfomc.edep = tshmc._energySum;
    tshinfomc.mom = std::sqrt(tshmc._mom.mag2());
    tshinfomc.cpos  = tshmc._cpos;

    // find the step midpoint
    const Straw& straw = tracker.getStraw(tshmc._strawId);
    CLHEP::Hep3Vector mcsep = GenVector::Hep3Vec(tshmc._cpos)-straw.getMidPoint();
    tshinfomc.len = mcsep.dot(straw.getDirection());
    CLHEP::Hep3Vector mdir = GenVector::Hep3Vec(tshmc._mom.unit());
    CLHEP::Hep3Vector mcperp = (mdir.cross(straw.getDirection())).unit();
    double dperp = mcperp.dot(mcsep);
    tshinfomc.twdot = mdir.dot(straw.getDirection());
    tshinfomc.dist = fabs(dperp);
    tshinfomc.ambig = dperp > 0 ? -1 : 1; // follow TrkPoca convention
    // use 2-line POCA here
    TwoLinePCA pca(GenVector::Hep3Vec(tshmc._cpos),mdir,straw.getMidPoint(),straw.getDirection());
    tshinfomc.doca = pca.dca();
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

    if (primary.primarySimParticles().empty()) {
      throw cet::exception("Simulation")<<"InfoMCStructHelper: No Primary Particle found" << std::endl;
    }
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
      std::vector<int> const& vids, double target_time) {

    GeomHandle<DetectorSystem> det;
    GlobalConstantsHandle<ParticleDataList> pdt;
    static CLHEP::Hep3Vector vpoint_mu2e = det->toMu2e(CLHEP::Hep3Vector(0.0,0.0,0.0));

    const auto& mcsteps = kseedmc._vdsteps;
    double dmin = std::numeric_limits<double>::max();
    for (const auto& i_mcstep : mcsteps) {
      for(auto vid : vids) {
        if (i_mcstep._vdid == vid) {
          // take the VD step with the time closest to target_time
          // this is so that we can take the correct step when looking at upstream/downstream trachs
          double corrected_time = fmod(i_mcstep._time, 1695); // VDStep is created with the time offsets included
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
}
