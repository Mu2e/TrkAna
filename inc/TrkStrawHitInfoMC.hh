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
    Int_t pdg, gen, proc; // PDG particle code, generator code and process code of the particle which caused the electronics to cross threshold in simulation
    MCRelationship rel; // relationship (same, mother, daughter, sibling, unrelated) of this particle to the particle generating most of the hits on this track
    Float_t t0;  // true time this particle passed closest to this wire
    Float_t tdrift;  // true drift time
    Float_t rdrift;  // true drift time
    Float_t tprop;  // true signal propagation time
    Float_t dist;  // true transverse distance between the cluster and the wire
    Float_t doca;  // true transverse distance at POCA of the particle to the wire
    Float_t len;   // true distance from the cluster to the straw center
    Float_t edep;  // true energy deposit sum by trigger particles in the straw gas
    Float_t mom;   // true particle momentum at the POCA
    Float_t twdot; // dot product between track and wire directions
    XYZVectorF cpos; // threshold cluster position
    Int_t ambig;   // true left-right ambiguity = true angular momentum sign of the particle WRT the wire
    Int_t earlyend;   // true end of the early signal (cal =0 or HV=1)
    TrkStrawHitInfoMC() : pdg(-1), gen(-1), proc(-1),
    t0(-1000.0),  dist(-1000.0), doca(-1000.0), len(-1000.0),
    edep(-1000.0), mom(-1000.0), twdot(-1000.0), ambig(-100), earlyend(-1) {}
  };
}
#endif
