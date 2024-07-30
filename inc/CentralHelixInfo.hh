//
// CentralHelixInfo: branch for CentralHelix track parameterization used for field-on cosmic tracks
// All momenta are in units of MeV/c, time in nsec WRT when the proton bunch pulse peak hits the production target,
// positions are in mm WRT the center of the tracker.
// Dave Brown (LBNL)
//
#ifndef CentralHelixInfo_HH
#define CentralHelixInfo_HH
#include "TrkAna/inc/RootVectors.hh"
#include "Offline/DataProducts/inc/SurfaceId.hh"
namespace mu2e
{
  struct CentralHelixInfo {
    // central helix parameters
    float d0=0,phi0=0,omega=0,z0=0,tanDip=0,t0=0;
    float d0err=0,phi0err=0,omegaerr=0,z0err=0,tanDiperr=0,t0err=0;
    // max radius (assuming geometric extrapolation).  This member is deprecated
    // in favor of explicit extrapolation to the OPA
    float maxr = 0;
    void reset() { *this = CentralHelixInfo(); }
  };
}
#endif
