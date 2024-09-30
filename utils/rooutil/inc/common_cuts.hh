//
// This file contains common cut functions that you might want to use.
// You can use these in your own functions too
//

#ifndef common_cuts_hh_
#define common_cuts_hh_

#include "TrkAna/utils/rooutil/inc/Track.hh"
#include "TrkAna/utils/rooutil/inc/TrackSegment.hh"

// Track Types
bool is_e_minus(const Track& track) {
  if (track.trk->pdg==11) { return true; }
  else { return false; }
}

bool is_e_plus(const Track& track) {
  if (track.trk->pdg==-11) { return true; }
  else { return false; }
}

bool is_mu_minus(const Track& track) {
  if (track.trk->pdg==13) { return true; }
  else { return false; }
}

bool is_mu_plus(const Track& track) {
  if (track.trk->pdg==-13) { return true; }
  else { return false; }
}


// Track Segment Locations
bool tracker_entrance(const TrackSegment& segment) {
  if (segment.trkfit->sid==mu2e::SurfaceIdDetail::TT_Front) { return true; }
  else { return false; }
}

bool tracker_middle(const TrackSegment& segment) {
  if (segment.trkfit->sid==mu2e::SurfaceIdDetail::TT_Mid) { return true; }
  else { return false; }
}

bool tracker_exit(const TrackSegment& segment) {
  if (segment.trkfit->sid==mu2e::SurfaceIdDetail::TT_Back) { return true; }
  else { return false; }
}


#endif
