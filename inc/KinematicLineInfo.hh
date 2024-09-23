//
// KinematicLineInfo: branch for KinematicLine track parameterization used for field-off cosmics
// All momenta are in units of MeV/c, time in nsec WRT when the proton bunch pulse peak hits the production target,
// positions are in mm WRT the center of the tracker.
// Dave Brown (LBNL)
//
#ifndef KinematicLineInfo_HH
#define KinematicLineInfo_HH

namespace mu2e
{
  struct KinematicLineInfo {
    float  d0=0, phi0=0, z0=0, theta=0, mom=0,t0=0;
    float  d0err=0, phi0err=0, z0err=0, thetaerr=0, momerr=0,t0err=0;
    void reset() { *this = KinematicLineInfo(); }
  };
}
#endif
