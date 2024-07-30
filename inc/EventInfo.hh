//
// EventInfo: branch to store event-level information
// Dave Brown (LBNL)
//
#ifndef EventInfo_HH
#define EventInfo_HH
#include <string>
namespace mu2e
{
  struct EventInfo {
    int event = 0; // event number
    int run = 0; // run number
    int subrun = 0; // subrun number
    int nprotons = 0; // estimated # of protons on target for this microbunch
    float pbtime = 0.0; // estimated proton bunch time
    float  pbterr = 0.0; // estimated proton bunch time uncertainty
    void reset() {*this = EventInfo(); }
  };
}
#endif
