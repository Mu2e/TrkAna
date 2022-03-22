//
// Module that finds the CrvCoincidenceCluster
// closest in time to a KalSeed
//
// Original author: Andy Edmonds 2022-03-14
//

// Framework includes.
#include "art/Framework/Core/EDProducer.h"
#include "art/Framework/Principal/Event.h"
#include "art/Framework/Principal/SubRun.h"
#include "art/Framework/Principal/Handle.h"
#include "art/Framework/Core/ModuleMacros.h"
#include "fhiclcpp/types/Atom.h"
#include "fhiclcpp/types/OptionalAtom.h"
#include "fhiclcpp/types/Table.h"
#include "fhiclcpp/types/OptionalSequence.h"

#include "TrkAna/inc/BestCrvAssns.hh"

// C++ includes.
#include <iostream>
#include <string>
#include <cmath>

using namespace std;

namespace mu2e {

  class BestCrvHitDeltaT : public art::EDProducer {

  public:
    struct Config {
      using Name=fhicl::Name;
      using Comment=fhicl::Comment;

      fhicl::Atom<art::InputTag> kalSeedTag{Name("kalSeedTag"), Comment("art::InputTag for KalSeedCollection")};
      fhicl::Atom<art::InputTag> crvCoincidenceTag{Name("crvCoincidenceTag"), Comment("art::InputTag for CrvCoincidenceClusterCollection")};
    };
    typedef art::EDProducer::Table<Config> Parameters;

    explicit BestCrvHitDeltaT(const Parameters& conf);
    virtual ~BestCrvHitDeltaT() { }

    void beginJob();
    void produce(art::Event& e);

  private:

    // fhicl parameters
    art::InputTag _kalSeedTag;
    art::InputTag _crvCoincidenceTag;
  };

  BestCrvHitDeltaT::BestCrvHitDeltaT(const Parameters& conf):
    art::EDProducer(conf),
    _kalSeedTag(conf().kalSeedTag()),
    _crvCoincidenceTag(conf().crvCoincidenceTag())
  {  
    produces<BestCrvAssns>();
  }

  void BestCrvHitDeltaT::beginJob( ){  }

  void BestCrvHitDeltaT::produce(art::Event& event) {

    const auto& kalSeedHandle = event.getValidHandle<KalSeedCollection>(_kalSeedTag);
    const auto& crvCoincidenceHandle = event.getValidHandle<CrvCoincidenceClusterCollection>(_crvCoincidenceTag);
    auto outAssns = std::make_unique<BestCrvAssns>();

    for (size_t i_kalSeed = 0; i_kalSeed != kalSeedHandle->size(); ++i_kalSeed) {
      const auto& kalSeed = kalSeedHandle->at(i_kalSeed);
      size_t i_bestCrvCoinc = -1;
      float mindt=1.0e9;
      float t0 = kalSeed.t0().t0();
      for(size_t i_crvCoinc = 0; i_crvCoinc != crvCoincidenceHandle->size(); ++i_crvCoinc) {
	const auto& crvCoinc = crvCoincidenceHandle->at(i_crvCoinc);
	auto const& crvStartTime = crvCoinc.GetStartTime();
	auto const& crvEndTime = crvCoinc.GetEndTime();
	float dt = std::min(fabs(crvStartTime-t0), fabs(crvEndTime-t0) );
	if(dt < mindt){
	  mindt =dt;
	  i_bestCrvCoinc = i_crvCoinc;
	}
      }
      if (i_bestCrvCoinc>=0) {
	auto kalSeedPtr = art::Ptr<KalSeed>(kalSeedHandle, i_kalSeed);
	auto crvCoincPtr = art::Ptr<CrvCoincidenceCluster>(crvCoincidenceHandle, i_bestCrvCoinc);
	outAssns->addSingle(kalSeedPtr, crvCoincPtr);
      }
    }
    event.put(std::move(outAssns));
  }
}  // end namespace mu2e

// Part of the magic that makes this class a module.
// create an instance of the module.  It also registers
using mu2e::BestCrvHitDeltaT;
DEFINE_ART_MODULE(BestCrvHitDeltaT);
