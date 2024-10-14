//
// CentralHelixInfo: array of arrays branch for CentralHelix track parameterization (used for field-on cosmic tracks). Example structure: [ [trk1_surfA, trk1_surfB, ...], [trk2_surf_A, trk2_surfC], ... [ trkN_surfB, trkN_surfC] ]
// All momenta are in units of MeV/c, time in nsec WRT when the proton bunch pulse peak hits the production target,
// positions are in mm WRT the center of the tracker.
// Dave Brown (LBNL)
//
#ifndef CentralHelixInfo_HH
#define CentralHelixInfo_HH
#include "EventNtuple/inc/RootVectors.hh"
#include "Offline/DataProducts/inc/SurfaceId.hh"
namespace mu2e
{
  struct CentralHelixInfo {
    // central helix parameters
    float d0 = 0; // d0 parameter of this CentralHelix segment [mm], see Figure 1 of DocDB-46577
    float phi0 = 0; // phi0 parameter of this CentralHelix segment, see Figure 1 of DocDB-46577
    float omega = 0; // omega parameter of this CentralHelix segment, see Figure 1 of DocDB-46577
    float z0 = 0; // z0 parameter of this CentralHelix segment [mm], see Figure 1 of DocDB-46577
    float tanDip = 0; // tandip parameter of this CentralHelix segment, see Figure 1 of DocDB-46577
    float t0 = 0; // time of this CentralHelix segment [ns], see Figure 1 of DocDB-46577
    float d0err = 0; // uncertainty on d0 parameter of this CentralHelix segment [mm]
    float phi0err = 0; // uncertainty on phi0 parameter of this CentralHelix segment
    float omegaerr = 0; // uncertainty on omega parameter of this CentralHelix segment
    float z0err = 0; // uncertainty on z0 parameter of this CentralHelix segment [mm]
    float tanDiperr = 0; // uncertainty on tandip parameter of this CentralHelix segment
    float t0err = 0; // uncertainty on time of this CentralHelix segment [ns]
    float maxr = 0; // max radius (assuming geometric extrapolation).  This member is DEPRECATED in favor of explicit extrapolation to the OPA
    void reset() { *this = CentralHelixInfo(); }
  };
}
#endif
