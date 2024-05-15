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
    Int_t nprotons; // estimated # of protons on target for this microbunch
    Float_t pbtime, pbterr; // estimated proton bunch time (and error)
    void reset() {
      eventid = runid = subrunid = nprotons = 0;
      pbtime = 0; pbterr = -1;
    }
  };
  struct EventInfoMC {
    Int_t nprotons; // MC true # of protons on target for this microbunch
    Float_t pbtime; // MC true proton bunch time
    void reset() { nprotons = 0; pbtime = 0.0; }
  };
}
#endif
