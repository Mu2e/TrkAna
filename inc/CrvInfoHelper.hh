#include <string>

#include "TrkAna/inc/CrvHitInfoReco.hh"
#include "TrkAna/inc/CrvHitInfoMC.hh"
#include "TrkAna/inc/CrvWaveformInfo.hh"
#include "TrkAna/inc/CrvSummaryReco.hh"
#include "TrkAna/inc/CrvSummaryMC.hh"
#include "TrkAna/inc/CrvPlaneInfoMC.hh"
#include "TrkAna/inc/CrvPulseInfoReco.hh"
#include "Offline/RecoDataProducts/inc/CrvCoincidenceCluster.hh"
#include "Offline/RecoDataProducts/inc/CrvRecoPulse.hh"
#include "Offline/RecoDataProducts/inc/CrvDigi.hh"
#include "Offline/MCDataProducts/inc/CrvDigiMC.hh"
#include "Offline/MCDataProducts/inc/CrvStep.hh"
#include "Offline/MCDataProducts/inc/SimParticle.hh"
#include "Offline/MCDataProducts/inc/CrvCoincidenceClusterMC.hh"
#include "Offline/MCDataProducts/inc/MCTrajectory.hh"
#include "art/Framework/Principal/Handle.h"

namespace mu2e
{
  class CrvInfoHelper
  {
    public:

      CrvInfoHelper() {}

      static void FillCrvHitInfoCollections(
          art::Handle<CrvCoincidenceClusterCollection> const& crvCoincidences,
          art::Handle<CrvCoincidenceClusterMCCollection> const& crvCoincidencesMC,
          art::Handle<CrvRecoPulseCollection> const& crvRecoPulses,
          art::Handle<CrvStepCollection> const& crvSteps,
          art::Handle<MCTrajectoryCollection> const& mcTrajectories,
          CrvHitInfoRecoCollection &recoInfo, CrvHitInfoMCCollection &MCInfo,
          CrvSummaryReco &recoSummary, CrvSummaryMC &MCSummary,
          CrvPlaneInfoMCCollection &MCInfoPlane, double crvPlaneY);

      static void FillCrvPulseInfoCollections(
          art::Handle<CrvRecoPulseCollection> const& crvRecoPulses,
          art::Handle<CrvDigiMCCollection> const& crvDigiMCs,
          art::Handle<CrvDigiCollection> const& crvDigis,
          CrvPulseInfoRecoCollection &recoInfo, CrvHitInfoMCCollection &MCInfo, CrvWaveformInfoCollection &waveformInfo);

    private:
      static const art::Ptr<SimParticle> &FindPrimaryParticle(const art::Ptr<SimParticle> &simParticle)
      {
        return simParticle->hasParent() ? FindPrimaryParticle(simParticle->parent()) : simParticle;
      }
      static const SimParticle &FindPrimaryParticle(const SimParticle &simParticle)
      {
        return simParticle.hasParent() ? *FindPrimaryParticle(simParticle.parent()) : simParticle;
      }
      static const art::Ptr<SimParticle> &FindParentParticle(const art::Ptr<SimParticle> &simParticle)
      {
        return simParticle->hasParent() ? simParticle->parent() : simParticle;
      }
      static const art::Ptr<SimParticle> &FindGParentParticle(const art::Ptr<SimParticle> &simParticle)
      {
        const art::Ptr<SimParticle> &parentParticle = simParticle->hasParent() ? simParticle->parent() : simParticle;
        return parentParticle->hasParent() ? parentParticle->parent() : parentParticle;
      }

      static const int _trajectorySimParticleId = 300001;  //only temporarily here for some tests
  };

}
