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
    Int_t nhits = -1; // number of matched hits in the track generated by this particle
    Int_t nactive = -1; // number of active matched hits in the track generated by this particle
    Int_t rank = -1; // rank of this particle, by # of associated hits
    Int_t pdg = -1; // true PDG code
    Int_t proc = -1; // process code
    Int_t gen = -1; // generator code
    Float_t time = -1.0;  // Origin time of the SimParticle
    Int_t index; // index into the SimInfo vector
    XYZVectorF mom = XYZVectorF();  // origin momentumof the SimParticle
    XYZVectorF pos = XYZVectorF();  // origin position of the SimParticle
    MCRelationship prirel = MCRelationship::none; // relationship to the event primary particles
    MCRelationship trkrel = MCRelationship::none; // relationship to the particle that created hits in the track
    void reset() { *this = SimInfo(); }
  };
}
#endif
