#include "EventNtuple/utils/rooutil/inc/RooUtil.hh"
#include "EventNtuple/utils/rooutil/inc/common_cuts.hh"

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

  // Now loop through the events and print the number of tracks in each event
  for (int i_event = 0; i_event < util.GetNEvents(); ++i_event) {
    const auto& event = util.GetEvent(i_event);
    std::cout << "" << event.evtinfo->run << ":" << event.evtinfo->subrun << ":" << event.evtinfo->event << " has: " << std::endl;
    std::cout << "pbtime (reco) = " << event.evtinfo->pbtime << " ns, pbtime (MC) = " << event.evtinfomc->pbtime << " ns" << std::endl;
    const auto& all_tracks = event.GetTracks();
    const auto& good_tracks = event.GetTracks(good_track);
    std::cout << all_tracks.size() << " total tracks and " << good_tracks.size() << " good tracks" << std::endl;

    int i_track = 0;
    for (const auto& track : good_tracks) {
      ++i_track;
      std::cout << "  Track #" << i_track << " has " << track.trk->nhits << " hits and " << track.trk->nactive << " active hits (fit consistency = " << track.trk->fitcon << ")";

      const auto& all_segments = track.GetSegments();
      std::cout << "  and " << all_segments.size() << " segments:" << std::endl;
      for (const auto& segment : all_segments) {
        std::cout << "    surfaceID " << segment.trkseg->sid << ": z = " << segment.trkseg->pos.z() << " mm, t = " << segment.trkseg->time << " ns, p = " << segment.trkseg->mom.R() << " MeV/c" << std::endl;
      }
    }
  }
}
