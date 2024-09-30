#ifndef Event_hh_
#define Event_hh_

#include "TrkAna/inc/EventInfo.hh"
#include "TrkAna/inc/TrkInfo.hh"

#include "TTree.h"

struct Event {
  Event(TTree* ntuple) {
    ntuple->SetBranchAddress("evtinfo", &this->evtinfo);
    ntuple->SetBranchAddress("trk", &this->trk);
  };

  int nTracks() const { return trk->size(); }
  mu2e::TrkInfo getTrack(size_t i_track) const { return trk->at(i_track); }

  mu2e::EventInfo* evtinfo = nullptr;
  std::vector<mu2e::TrkInfo>* trk = nullptr;
};

#endif
