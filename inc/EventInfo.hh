//
// simple struct to record event-level information
// Dave Brown (LBNL)
//
#ifndef EventInfo_HH
#define EventInfo_HH
#include "Rtypes.h"
#include <string>
namespace mu2e
{
  struct EventInfo {
    Int_t eventid, runid, subrunid; // run/event identification
    Int_t nprotons; // # of protons on target for this microbunch
    void reset() {
      eventid = runid = subrunid = nprotons = 0;
    }
  };
}
#endif
