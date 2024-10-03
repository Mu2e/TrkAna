//
// An example of how to plot the momentum of electrons at the tracker entrance
// This uses cut functions defined in common_cuts.hh
//

#include "TrkAna/utils/rooutil/inc/RooUtil.hh"
#include "TrkAna/utils/rooutil/inc/common_cuts.hh"

#include "TH1F.h"

void PlotEntranceMomentum(std::string filename) {

  // Create the histogram you want to fill
  TH1F* hRecoMom = new TH1F("hRecoMom", "Reconstructed Momentum at Tracker Entrance", 50,95,110);

  // Set up RooUtil
  RooUtil util(filename);

  // Loop through the events
  for (int i_event = 0; i_event < util.GetNEvents(); ++i_event) {
    // Get the next event
    const auto& event = util.GetEvent(i_event);

    // Get the e_minus tracks from the event
    const auto& e_minus_tracks = event.GetTracks(is_e_minus);

    // Loop through the e_minus tracks
    for (const auto& track : e_minus_tracks) {

      // Get the track segments at the tracker entrance
      const auto& trk_ent_segments = track.GetSegments(tracker_entrance);

      // Loop through the tracker entrance track segments
      for (const auto& segment : trk_ent_segments) {

        // Fill the histogram
        hRecoMom->Fill(segment.trkseg->mom.R());
      }
    }
  }

  // Draw the histogram
  hRecoMom->Draw("HIST E");
}
