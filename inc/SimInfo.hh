//
// structs used to record SimParticle information in TTrees.
// All momenta are in units of MeV/c, time in nsec WRT when the proton bunch pulse peak hits the production target,
// positions are in mm WRT the center of the tracker.
// Andy Edmonds (March 2019)
//
#ifndef SimInfo_HH
#define SimInfo_HH
#include "Offline/DataProducts/inc/GenVector.hh"
#include "Rtypes.h"
namespace mu2e
{
// general info about the SimParticle which was simulated
  struct SimInfo {
    bool valid = false; // true/false as to whether the data is valid
    Int_t pdg = -1; // true PDG code
    Int_t gen = -1; // generator code
    Float_t time = -1.0;  // time of this step
    XYZVectorF mom = XYZVectorF();  // particle momentum at the start of this step
    XYZVectorF pos = XYZVectorF();  // particle position at the start of this step
    Int_t generation = 1000; // where 0=current generation, -1 is previous generation, etc..
    void reset() { *this = SimInfo(); }
  };
}
#endif
