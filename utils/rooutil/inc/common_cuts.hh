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

// Track Segment Directions
bool is_downstream(const TrackSeg& track_seg) {
  // the sign of p_z tells us whether this segment is going upstream or downstream
  if (segment.trkseg->mom.z() > 0) {
      return true;
  }
  else { return false; }
}

bool is_upstream(const TrackSeg& track_seg) {
  // the sign of p_z tells us whether this segment is going upstream or downstream
  if (segment.trkseg->mom.z() < 0) {
      return true;
  }
  else { return false; }
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


// More complex cuts

// A track is a reflected track if we have both an upstream and a downstream segment at the tracker entrance
bool is_reflected(const Track& track) {
  bool have_upstream = false;
  bool have_downstream = false;
  for (const auto& track_seg : track.segments) {
    if (track_entrance(track_seg)) {
      if (is_upstream(track_seg)) {
        have_upstream = true;
      }
      if (is_downstream(track_seg)) {
        have_downstream = true;
      }
    }
  }
  if (have_upstream && have_downstream) {
    return true;
  }
  else {
    return false;
  }
}


#endif
