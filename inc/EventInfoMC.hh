//
// EventInfoMC: branch to store MC event-level information
// Dave Brown (LBNL)
//
#ifndef EventInfoMC_HH
#define EventInfoMC_HH
#include <string>
namespace mu2e
{
  struct EventInfoMC {
    int nprotons = 0 ; // MC true # of protons on target for this microbunch
    float pbtime = 0; // MC true proton bunch time
    void reset() {*this = EventInfoMC(); }
  };
}
#endif
