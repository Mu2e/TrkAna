#ifndef Event_hh_
#define Event_hh_

#include "TrkAna/inc/EventInfo.hh"

#include "TTree.h"

struct Event {
  Event(TTree* ntuple) {
    ntuple->SetBranchAddress("evtinfo", &this->evtinfo);
  };

  mu2e::EventInfo* evtinfo = nullptr;
};

#endif
