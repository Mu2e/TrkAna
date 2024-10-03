#ifndef Event_hh_
#define Event_hh_

#include "TrkAna/inc/EventInfo.hh"
#include "TrkAna/inc/EventInfoMC.hh"

#include "TrkAna/utils/rooutil/inc/Track.hh"

#include "TTree.h"

struct Event {
  Event(TTree* ntuple, bool debug = false) : debug(debug) {
    if (debug) {
      std::cout << "Event::Event(): Setting branch addresses..." << std::endl;
    }

    ntuple->SetBranchAddress("evtinfo", &this->evtinfo);
    ntuple->SetBranchAddress("trk", &this->trk);
    ntuple->SetBranchAddress("trksegs", &this->trksegs);

    // Check if the MC branches exist
    if (ntuple->GetBranch("evtinfomc")) {
      ntuple->SetBranchAddress("evtinfomc", &this->evtinfomc);
    }

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
      Track track(&(trk->at(i_track)), &(trksegs->at(i_track)), debug); // passing the addresses of the underlying structs
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

  int CountTracks() const { return tracks.size(); }
  int CountTracks(TrackCut cut) const {
    Tracks select_tracks = GetTracks(cut);
    return select_tracks.size();
  }

  Tracks tracks;

  bool debug = false;

  // Pointers to the data
  mu2e::EventInfo* evtinfo = nullptr;
  mu2e::EventInfoMC* evtinfomc = nullptr;

  std::vector<mu2e::TrkInfo>* trk = nullptr;
  std::vector<std::vector<mu2e::TrkSegInfo>>* trksegs = nullptr;
};

#endif
