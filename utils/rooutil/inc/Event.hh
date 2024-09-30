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

  void Update() {
    tracks.clear();
    for (int i_track = 0; i_track < nTracks(); ++i_track) {
      Track track(&(trk->at(i_track)), &(trkfit->at(i_track)));
      tracks.emplace_back(track);
    }
  }


  int nTracks() const { return trk->size(); }
  Track getTrack(size_t i_track) const { return Track(&trk->at(i_track), &trkfit->at(i_track)); }

  Tracks GetTracks(TrackCut cut) const {
    Tracks select_tracks;
    for (const auto& track : tracks) {
      if (cut(track)) {
        select_tracks.emplace_back(track);
      }
    }
    return select_tracks;
  }

  Tracks tracks;

  mu2e::EventInfo* evtinfo = nullptr;
  std::vector<mu2e::TrkInfo>* trk = nullptr;
  std::vector<std::vector<mu2e::TrkFitInfo>>* trkfit = nullptr;
};

#endif
