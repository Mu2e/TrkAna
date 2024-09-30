//
// This file contains common cut functions that you might want to use.
// You can use these in your own functions too
//

#ifndef common_cuts_hh_
#define common_cuts_hh_

#include "TrkAna/utils/rooutil/inc/Track.hh"

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

#endif
