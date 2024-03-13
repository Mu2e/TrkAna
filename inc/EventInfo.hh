//
// simple struct to record event-level information
// Dave Brown (LBNL)
//
#ifndef EventInfo_HH
#define EventInfo_HH
#include <string>
namespace mu2e
{
  struct EventInfo {
    int event = 0;
    int run = 0;
    int subrun = 0; // run/event identification
    int nprotons = 0; // estimated # of protons on target for this microbunch
    float pbtime = 0.0;
    float  pbterr = 0.0; // estimated proton bunch time (and error)
    void reset() {*this = EventInfo(); }
  };
  struct EventInfoMC {
    int nprotons = 0 ; // MC true # of protons on target for this microbunch
    float pbtime = 0; // MC true proton bunch time
    void reset() {*this = EventInfoMC(); }
  };
}
#endif
