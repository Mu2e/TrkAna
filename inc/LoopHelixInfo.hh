//
// LoopHelixInfo: branch for LoopHelix track parameterization used for looping tracks
// All momenta are in units of MeV/c, time in nsec WRT when the proton bunch pulse peak hits the production target,
// positions are in mm WRT the center of the tracker.
// Dave Brown (LBNL)
//
#ifndef LoopHelixInfo_HH
#define LoopHelixInfo_HH

namespace mu2e
{
  struct LoopHelixInfo {
    //  These members are deprecated
    // in favor of explicit extrapolation to the OPA
    float maxr = 0; // max radius (assuming geometric extrapolation) DEPRECATED
    float d0 = 0; // d0 (unsigned!)  DEPRECATED
    float tanDip = 0; // tanDip  DEPRECATED
    // loop helix parameters
    float rad=0,lam=0,cx=0,cy=0,phi0=0,t0=0;
    float raderr=0,lamerr=0,cxerr=0,cyerr=0,phi0err=0,t0err=0;
    void reset() { *this = LoopHelixInfo(); }
  };
}
#endif
