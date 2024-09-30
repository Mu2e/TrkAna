#ifndef Event_hh_
#define Event_hh_

#include "TrkAna/inc/EventInfo.hh"

#include "TrkAna/utils/rooutil/inc/Track.hh"

#include "TTree.h"

struct Event {
  Event(TTree* ntuple) {
    ntuple->SetBranchAddress("evtinfo", &this->evtinfo);
    ntuple->SetBranchAddress("trk", &this->trk);
    ntuple->SetBranchAddress("trkfit", &this->trkfit);
  };

  int nTracks() const { return trk->size(); }
  Track getTrack(size_t i_track) const { return Track(&trk->at(i_track), &trkfit->at(i_track)); }

  mu2e::EventInfo* evtinfo = nullptr;
  std::vector<mu2e::TrkInfo>* trk = nullptr;
  std::vector<std::vector<mu2e::TrkFitInfo>>* trkfit = nullptr;
};

#endif
