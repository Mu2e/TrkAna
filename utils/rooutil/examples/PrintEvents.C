#include "TrkAna/utils/rooutil/inc/RooUtil.hh"

#include <iostream>

bool good_track(const Track& track) {
  if (track.trk->fitcon > 1e-3) {
    return true;
  }
  else {
    return false;
  }
}

void PrintEvents(std::string filename) {

  RooUtil util(filename);
  std::cout << filename << " has " << util.GetNEvents() << " events" << std::endl;

  // Now loop through the events and print the number of tracks in each event
  for (int i_event = 0; i_event < util.GetNEvents(); ++i_event) {
    const auto& event = util.GetEvent(i_event);
    std::cout << "" << event.evtinfo->run << ":" << event.evtinfo->subrun << ":" << event.evtinfo->event << " has " << event.nTracks() << " tracks" << std::endl;

    for (int i_track = 0; i_track < event.nTracks(); ++i_track) {
      const auto& track = event.getTrack(i_track);
      std::cout << "  Track #" << i_track+1 << " has " << track.trk->nhits << " hits and " << track.trk->nactive << " active hits (fit consistency = " << track.trk->fitcon << ")";
      if (good_track(track)) {
        std::cout << " GOOD TRACK";
      }
      else {
        std::cout << " BAD TRACK";
      }
      std::cout << std::endl << "  and " << track.trkfit->size() << " segments:" << std::endl;

      for (const auto& trkfit : *track.trkfit) {
        std::cout << "    surfaceID " << trkfit.sid << ": p = " << trkfit.mom.R() << " MeV/c" << std::endl;
      }
    }
  }
}
