#include <string>

#include "TrkAna/inc/CrvHitInfoReco.hh"
#include "TrkAna/inc/CrvHitInfoMC.hh"
#include "TrkAna/inc/CrvWaveformInfo.hh"
#include "TrkAna/inc/CrvSummaryReco.hh"
#include "TrkAna/inc/CrvSummaryMC.hh"
#include "TrkAna/inc/CrvPlaneInfoMC.hh"
#include "TrkAna/inc/CrvPulseInfoReco.hh"
#include "Offline/MCDataProducts/inc/SimParticle.hh"

namespace mu2e
{
  class CrvInfoHelper
  {
    public:

      CrvInfoHelper() {}

      static void FillCrvHitInfoCollections(
          const& art::Handle<CrvCoincidenceClusterCollection> crvCoincidences,
          const& art::Handle<CrvCoincidenceClusterMCCollection> crvCoincidencesMC,
          const& art::Handle<CrvRecoPulseCollection> crvRecoPulses,
          const& art::Handle<CrvStepCollection> crvSteps,
          const& art::Handle<MCTrajectoryCollection> mcTrajectories,
          CrvHitInfoRecoCollection &recoInfo, CrvHitInfoMCCollection &MCInfo,
          CrvSummaryReco &recoSummary, CrvSummaryMC &MCSummary,
          CrvPlaneInfoMCCollection &MCInfoPlane, double crvPlaneY);

      static void FillCrvPulseInfoCollections(
          const& art::Handle<CrvRecoPulseCollection> crvRecoPulses,
          const& art::Handle<CrvWaveformCollection> crvWaveforms,
          const& art::Handle<CrvDigiCollection> crvDigis,
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
