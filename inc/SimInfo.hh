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
#include "TrkAna/inc/Names.hh"
#include "Rtypes.h"
namespace mu2e
{
// general info about the SimParticle which was simulated
  struct SimInfo {
    Int_t _pdg, _gen; // true PDG code, generator code
    Float_t _time;  // time of this step
    Float_t _mom; // scalar momentum at the start of this step
    Float_t _costh; // cos(theta), where theta is angle between particle's momentum and z-axis
    Float_t _phi;   // azimuthal angle of particle's momentum vector
    XYZVectorF _pos;  // particle position at the start of this step
    SimInfo() { reset(); }
    void reset() { _pdg = _gen = -1; _time = -1.0; _mom = 0; _costh = 0; _phi = 0; _pos = XYZVectorF(); }
    static std::string leafnames() { static std::string leaves;
      leaves = std::string("pdg/I:gen/I:t0/F:mom/F:costh/F:phi/F:") + Names::XYZnames("pos");
      return leaves;
    }
  };
}
#endif
