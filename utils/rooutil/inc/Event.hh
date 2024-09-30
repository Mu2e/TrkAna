#ifndef Event_hh_
#define Event_hh_

#include "TrkAna/inc/EventInfo.hh"

#include "TrkAna/utils/rooutil/inc/Track.hh"

#include "TTree.h"

struct Event {
  Event(TTree* ntuple, bool debug = false) : debug(debug) {
    if (debug) {
      std::cout << "Event::Event(): Setting branch addresses..." << std::endl;
    }

    ntuple->SetBranchAddress("evtinfo", &this->evtinfo);
    ntuple->SetBranchAddress("trk", &this->trk);
    ntuple->SetBranchAddress("trkfit", &this->trkfit);

    if (debug) {
      std::cout << "Event::Event(): All done." << std::endl;
    }
  };

  void Update() {
    if (debug) {
      std::cout << "Event::Update(): Clearing tracks from previous event..." << std::endl;
    }
    tracks.clear();

    for (int i_track = 0; i_track < nTracks(); ++i_track) {
      Track track(&(trk->at(i_track)), &(trkfit->at(i_track)));
      if (debug) {
        std::cout << "Event::Update(): Adding track #" << i_track << " to tracks..." << std::endl;
      }
      tracks.emplace_back(track);
    }

    if (debug) {
      std::cout << "Event::Update(): All done." << std::endl;
    }
  }


  int nTracks() const { return trk->size(); }

  Tracks GetTracks() const { return tracks; }
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

  bool debug = false;
};

#endif
