//
// LoopHelixInfo: array of array branch for LoopHelix track parameterization (used for looping tracks). Example structure: [ [trk1_surfA, trk1_surfB, ...], [trk2_surf_A, trk2_surfC], ... [ trkN_surfB, trkN_surfC] ]
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
    float maxr = 0; // max radius (assuming geometric extrapolation) [mm] DEPRECATED
    float d0 = 0; // d0 (unsigned!) [mm]  DEPRECATED
    float tanDip = 0; // tanDip  DEPRECATED
    // loop helix parameters
    float rad = 0; // transverse radius of this LoopHelix segment [mm], see Figure 1 of DocDB-46577
    float lam = 0; // longitudiinal wavelength of this LoopHelix segment [mm], see Figure 1 of DocDB-46577
    float cx = 0; // x-position of the center of this LoopHelix segment [mm], see Figure 1 of DocDB-46577
    float cy = 0; // y-position of the center of this LoopHelix segment [mm], see Figure 1 of DocDB-46577
    float phi0 = 0; // phi0 parameter of this LoopHelix sgement, see Figure 1 of DocDB-46577
    float t0 = 0; // time of this LoopHelix segment [ns]
    float raderr = 0; // uncertainty on transverse radius [mm]
    float lamerr = 0; // uncertainty on longitudinal wavelength [mm]
    float cxerr = 0; // uncertainty on x-position of the center [mm]
    float cyerr = 0; // uncertainty on y-position of the center [mm]
    float phi0err = 0; // uncertainty on phi0 parameter
    float t0err = 0; // uncertainty on time parameter [ns]
    void reset() { *this = LoopHelixInfo(); }
  };
}
#endif
