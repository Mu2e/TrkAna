//
// Namespace for collecting tools used in MC truth evaluation
// Original author: Dave Brown (LBNL) 8/10/2016
//
#ifndef TrkAna_InfoMCStructHelper_hh
#define TrkAna_InfoMCStructHelper_hh
#include "Offline/RecoDataProducts/inc/StrawHitIndex.hh"
#include "Offline/MCDataProducts/inc/StrawDigiMC.hh"
#include "Offline/MCDataProducts/inc/StrawDigiMCCollection.hh"
#include "Offline/MCDataProducts/inc/StepPointMCCollection.hh"

#include "Offline/RecoDataProducts/inc/KalSeed.hh"
#include "TrkAna/inc/TrkInfo.hh"
#include "TrkAna/inc/SimInfo.hh"
#include "TrkAna/inc/TrkStrawHitInfoMC.hh"
#include "TrkAna/inc/CaloClusterInfoMC.hh"
#include "Offline/MCDataProducts/inc/KalSeedMC.hh"
#include "BTrk/BbrGeom/HepPoint.h"
#include "Offline/MCDataProducts/inc/PrimaryParticle.hh"

#include "Offline/Mu2eUtilities/inc/SimParticleTimeOffset.hh"

#include <vector>
#include <functional>
namespace mu2e {

  class InfoMCStructHelper {

  private:
    art::InputTag _spctag;
    art::Handle<SimParticleCollection> _spcH;
    SimParticleTimeOffset _toff;
    double _mingood;

    void fillSimInfo(const art::Ptr<SimParticle>& sp, SimInfo& siminfo);
    void fillSimInfo(const SimParticle& sp, SimInfo& siminfo);

  public:

    struct Config {
      using Name=fhicl::Name;
      using Comment=fhicl::Comment;
      
      fhicl::Atom<art::InputTag> spctag{Name("SimParticleCollectionTag"), Comment("InputTag for the SimParticleCollection"), art::InputTag()};
      fhicl::Sequence<art::InputTag> toff{Name("TimeMaps"), Comment("List of SimParticle time maps to use")};
      fhicl::Atom<double> mingood{Name("MinGoodMomFraction"), Comment("Minimum fraction of the true particle's momentum for a digi to be described as \"good\"")};
    };

    InfoMCStructHelper(const Config& conf) :
      _spctag(conf.spctag()), _toff(conf.toff()), _mingood(conf.mingood()) {  };

    void updateEvent(const art::Event& event) {
      event.getByLabel(_spctag,_spcH);
      _toff.updateMap(event);
    }

    const SimParticleTimeOffset& getTimeMaps() const { return _toff; }
    void fillTrkInfoMC(const KalSeedMC& kseedmc, TrkInfoMC& trkinfomc);
    void fillTrkInfoMCDigis(const KalSeedMC& kseedmc, TrkInfoMC& trkinfomc);
    void fillHitInfoMC(const KalSeedMC& kseedmc, TrkStrawHitInfoMC& tshinfomc, const TrkStrawHitMC& tshmc);
    void fillSimAndPriInfo(const KalSeedMC& kseedmc, const PrimaryParticle& primary, SimInfo& priinfo, SimInfo& siminfo, SimInfo& parentinfo, SimInfo& gparentinfo);
    void fillTrkInfoMCStep(const KalSeedMC& kseedmc, TrkInfoMCStep& trkinfomcstep, std::vector<int> const& vids, double target_time);

    void fillHitInfoMCs(const KalSeedMC& kseedmc, std::vector<TrkStrawHitInfoMC>& tshinfomcs);
    void fillCaloClusterInfoMC(CaloClusterMC const& ccmc, CaloClusterInfoMC& ccimc);
  };
}

#endif
