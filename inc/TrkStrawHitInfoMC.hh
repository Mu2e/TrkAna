//
// Struct describing MC truth of single straw hit assigned to a track, for use in TTree diagnostics
//
#ifndef TrkStrawHitInfoMC_HH
#define TrkStrawHitInfoMC_HH
#include "Rtypes.h"
#include "Offline/DataProducts/inc/GenVector.hh"
#include "Offline/MCDataProducts/inc/MCRelationship.hh"
namespace mu2e
{
   struct TrkStrawHitInfoMC {
    Int_t pdg = -1;
    Int_t gen = -1;
    Int_t proc = -1; // PDG particle code, generator code and process code of the particle which caused the electronics to cross threshold in simulation
    Int_t ambig = -100;   // true left-right ambiguity = true angular momentum sign of the particle WRT the wire
    Int_t earlyend = -1;   // true end of the early signal (cal =0 or HV=1)
    MCRelationship rel = MCRelationship::none; // relationship (same, mother, daughter, sibling, unrelated) of this particle to the particle generating most of the hits on this track
    Float_t t0 = -1000.0;  // true time this particle passed closest to this wire
    Float_t tdrift = -1000.0;  // true drift time
    Float_t rdrift = -1000.0;  // true drift time
    Float_t tprop = -1000.0;  // true signal propagation time
    Float_t dist = -1000.0;  // true transverse distance between the cluster and the wire
    Float_t doca = -1000.0;  // true transverse distance at POCA of the particle to the wire
    Float_t len = -1000.0;   // true distance from the cluster to the straw center
    Float_t edep = -1000.0;  // true energy deposit sum by trigger particles in the straw gas
    Float_t mom = -1000.0;   // true particle momentum at the POCA
    Float_t twdot = -1000.0; // dot product between track and wire directions
    Float_t tau = -1000.0; // threshold cluster distance to the wire along the perpedicular particle path
    Float_t cdist = -1000.0; // threshold cluster distance to the wire
    XYZVectorF cpos; // threshold cluster position
  };
}
#endif
