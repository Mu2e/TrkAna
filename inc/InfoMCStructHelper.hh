//
// Namespace for collecting tools used in MC truth evaluation
// Original author: Dave Brown (LBNL) 8/10/2016
//
#ifndef TrkAna_InfoMCStructHelper_hh
#define TrkAna_InfoMCStructHelper_hh
#include "fhiclcpp/types/Atom.h"
#include "Offline/RecoDataProducts/inc/StrawHitIndex.hh"
#include "Offline/MCDataProducts/inc/StrawDigiMC.hh"
#include "Offline/MCDataProducts/inc/StepPointMC.hh"
#include "Offline/MCDataProducts/inc/CrvCoincidenceClusterMC.hh"

#include "Offline/RecoDataProducts/inc/KalSeed.hh"
#include "TrkAna/inc/TrkInfo.hh"
#include "TrkAna/inc/SimInfo.hh"
#include "TrkAna/inc/TrkStrawHitInfoMC.hh"
#include "TrkAna/inc/CaloClusterInfoMC.hh"
#include "TrkAna/inc/MCStepInfo.hh"
#include "TrkAna/inc/CrvHitInfoMC.hh"
#include "Offline/RecoDataProducts/inc/KalSeed.hh"
#include "Offline/MCDataProducts/inc/KalSeedMC.hh"
#include "BTrk/BbrGeom/HepPoint.h"
#include "Offline/MCDataProducts/inc/PrimaryParticle.hh"

#include <vector>
#include <functional>
namespace mu2e {

  class InfoMCStructHelper {

    private:
      art::InputTag _spctag;
      art::Handle<SimParticleCollection> _spcH;
      double _mingood;
      bool _onSpill; // onspill data flag, needed to decide if MC times should be wrapped.  Updated each event
      double _mbtime; // microbunch period (onspill wrapping time), only relevant for onspill
      double _maxdt; // maximum time difference between reco intersection and equivalent MC VD hit
      art::InputTag _ewMarkerTag;
      // map VirtualDetectorIds to the equivalen SurfaceIds
      std::map<VirtualDetectorId,SurfaceId> _vdmap;

      void fillSimInfo(const art::Ptr<SimParticle>& sp, SimInfo& siminfo);
      void fillSimInfo(const SimParticle& sp, SimInfo& siminfo);

    public:

      struct Config {
        using Name=fhicl::Name;
        using Comment=fhicl::Comment;

        fhicl::Atom<art::InputTag> spctag{Name("SimParticleCollectionTag"), Comment("InputTag for the SimParticleCollection"), art::InputTag()};
        fhicl::Atom<double> mingood{Name("MinGoodMomFraction"), Comment("Minimum fraction of the true particle's momentum for a digi to be described as \"good\"")};
        fhicl::Atom<art::InputTag> ewMarkerTag{ Name("EventWindowMarker"), Comment("EventWindowMarker producer"),"EWMProducer" };
        fhicl::Atom<double> maxvddt{Name("MaxVDDt"), Comment("Maximum time difference between reco and VirtualDetector time to associate")};
     };

      InfoMCStructHelper(const Config& conf);
      void updateEvent(const art::Event& event);

      void fillTrkInfoMC(const KalSeed& kseed, const KalSeedMC& kseedmc, std::vector<TrkInfoMC>& all_trkinfomcs);
      void fillTrkInfoMCDigis(const KalSeed& kseed, const KalSeedMC& kseedmc, TrkInfoMC& trkinfomc);
      void fillHitInfoMC(const KalSeedMC& kseedmc, TrkStrawHitInfoMC& tshinfomc, const TrkStrawHitMC& tshmc);
      void fillAllSimInfos(const KalSeedMC& kseedmc, const PrimaryParticle& primary, std::vector<std::vector<SimInfo>>& all_siminfos, int n_generations);
      void fillVDInfo(KalSeed const& kseed, const KalSeedMC& kseedmc, std::vector<std::vector<MCStepInfo>>& all_vdinfos);
      void fillHitInfoMCs(const KalSeedMC& kseedmc, std::vector<std::vector<TrkStrawHitInfoMC>>& all_tshinfomcs);
      void fillCaloClusterInfoMC(CaloClusterMC const& ccmc, std::vector<CaloClusterInfoMC>& ccimc);
      void fillExtraMCStepInfos(KalSeedMC const& kseedmc, StepPointMCCollection const& mcsteps,
      MCStepInfos& mcsic, MCStepSummaryInfo& mcssi);
  };
}

#endif
