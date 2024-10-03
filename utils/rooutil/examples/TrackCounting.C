#include "TrkAna/utils/rooutil/inc/RooUtil.hh"
#include "TrkAna/utils/rooutil/inc/common_cuts.hh"

#include <iostream>

void TrackCounting(std::string filename) {

  RooUtil util(filename);
  std::cout << filename << " has " << util.GetNEvents() << " events" << std::endl;

  // Now loop through the events and print the number of tracks in each event
  std::cout << "Run\tSubrun\tEvent\tN_trk\tN_e-\tN_e+\tN_mu-\tN_mu+" << std::endl;
  for (int i_event = 0; i_event < util.GetNEvents(); ++i_event) {
    const auto& event = util.GetEvent(i_event);

    int n_total_tracks = event.CountTracks();
    int n_e_minus_tracks = event.CountTracks(is_e_minus);
    int n_e_plus_tracks = event.CountTracks(is_e_plus);
    int n_mu_minus_tracks = event.CountTracks(is_mu_minus);
    int n_mu_plus_tracks = event.CountTracks(is_mu_plus);

    std::cout << event.evtinfo->run << "\t" << event.evtinfo->subrun << "\t" << event.evtinfo->event << "\t" << n_total_tracks << "\t" << n_e_minus_tracks << "\t" << n_e_plus_tracks << "\t" << n_mu_minus_tracks << "\t" << n_mu_plus_tracks << std::endl;
  }
}
