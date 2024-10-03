//
// This file contains common cut functions that you might want to use.
// You can use these in your own functions too
//

#ifndef common_cuts_hh_
#define common_cuts_hh_

#include "TrkAna/utils/rooutil/inc/Track.hh"
#include "TrkAna/utils/rooutil/inc/TrackSegment.hh"

// Track Particle Types
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

// Track Directions
bool is_downstream(const Track& track) {
  // Segments are time-ordered so check to see if the track always increases in z-position
  double first_z = track.GetSegments().at(0).trkseg->pos.z();
  double prev_z = first_z;
  for (const auto& segment : track.GetSegments()) {
    if (segment.trkseg->pos.z() < prev_z) { // we are now upstream of the previous segment so this is now a downstream track
      return false;
    }
  }
  return true; // we got to the end without turning upstream
}


// Track Segment Locations
bool tracker_entrance(const TrackSegment& segment) {
  if (segment.trkseg->sid==mu2e::SurfaceIdDetail::TT_Front) { return true; }
  else { return false; }
}

bool tracker_middle(const TrackSegment& segment) {
  if (segment.trkseg->sid==mu2e::SurfaceIdDetail::TT_Mid) { return true; }
  else { return false; }
}

bool tracker_exit(const TrackSegment& segment) {
  if (segment.trkseg->sid==mu2e::SurfaceIdDetail::TT_Back) { return true; }
  else { return false; }
}


#endif
