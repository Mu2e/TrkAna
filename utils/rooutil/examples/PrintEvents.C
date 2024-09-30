#include "TrkAna/utils/rooutil/inc/RooUtil.hh"
#include "TrkAna/utils/rooutil/inc/common_cuts.hh"

#include "TH1F.h"

#include <iostream>

bool good_track(const Track& track) {
  if (track.trk->fitcon > 1e-3 && is_e_minus(track)) {
    return true;
  }
  else {
    return false;
  }
}

void PrintEvents(std::string filename) {

  RooUtil util(filename);
  std::cout << filename << " has " << util.GetNEvents() << " events" << std::endl;

  TH1F* hRecoMom = new TH1F("hRecoMom", "Reconstructed Momentum at Tracker Entrance", 50,95,110);

  // Now loop through the events and print the number of tracks in each event
  for (int i_event = 0; i_event < util.GetNEvents(); ++i_event) {
    const auto& event = util.GetEvent(i_event);
    std::cout << "" << event.evtinfo->run << ":" << event.evtinfo->subrun << ":" << event.evtinfo->event << " has: " << std::endl;

    const auto& all_tracks = event.GetTracks();
    const auto& good_tracks = event.GetTracks(good_track);
    std::cout << all_tracks.size() << " total tracks and " << good_tracks.size() << " good tracks" << std::endl;

    int i_track = 0;
    for (const auto& track : all_tracks) {
      ++i_track;
      std::cout << "  Track #" << i_track << " has " << track.trk->nhits << " hits and " << track.trk->nactive << " active hits (fit consistency = " << track.trk->fitcon << ")";
      if (good_track(track)) {
        std::cout << " GOOD TRACK";
      }
      else {
        std::cout << " BAD TRACK";
      }
      std::cout << std::endl << "  and " << track.trkfit->size() << " segments:" << std::endl;
    }

    std::cout << "Now looping through the good tracks only..." << std::endl;
    for (const auto& track : good_tracks) {
      std::cout << "  This track has " << track.trk->nhits << " hits and " << track.trk->nactive << " active hits (fit consistency = " << track.trk->fitcon << ")" << std::endl;
      for (const auto& trkfit : *track.trkfit) {
        std::cout << "    surfaceID " << trkfit.sid << ": p = " << trkfit.mom.R() << " MeV/c" << std::endl;
        if (trkfit.sid == mu2e::SurfaceIdDetail::TT_Front) {
          hRecoMom->Fill(trkfit.mom.R());
        }
      }
    }
  }
  hRecoMom->Draw("HIST E");
}
