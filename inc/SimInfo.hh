//
// structs used to record SimParticle information in TTrees.
// All momenta are in units of MeV/c, time in nsec WRT when the proton bunch pulse peak hits the production target,
// positions are in mm WRT the center of the tracker.
// Andy Edmonds (March 2019)
//
#ifndef SimInfo_HH
#define SimInfo_HH
#include "Offline/DataProducts/inc/GenVector.hh"
#include "TrkAna/inc/helixpar.hh"
#include "Rtypes.h"
namespace mu2e
{
// general info about the SimParticle which was simulated
  struct SimInfo {
    bool valid; // true/false as to whether the data is valid
    Int_t pdg, gen; // true PDG code, generator code
    Float_t time;  // time of this step
    XYZVectorF mom;  // particle momentum at the start of this step
    XYZVectorF pos;  // particle position at the start of this step
    SimInfo() { reset(); }
    void reset() { valid = false; pdg = gen = -1; time = -1.0; mom =XYZVectorF(); pos = XYZVectorF(); }
  };
}
#endif
