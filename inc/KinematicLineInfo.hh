//
// KinematicLineInfo: array of arrays branch for KinematicLine track parameterization (used for field-off cosmics). Example structure: [ [trk1_surfA, trk1_surfB, ...], [trk2_surf_A, trk2_surfC], ... [ trkN_surfB, trkN_surfC] ]
// All momenta are in units of MeV/c, time in nsec WRT when the proton bunch pulse peak hits the production target,
// positions are in mm WRT the center of the tracker.
// Dave Brown (LBNL)
//
#ifndef KinematicLineInfo_HH
#define KinematicLineInfo_HH

namespace mu2e
{
  struct KinematicLineInfo {
    float d0 = 0; // d0 parameter of this KinematicLine segment, see Figure 1 of DocDB-46577
    float phi0 = 0; // phi0 parameter of this KinematicLine segment, see Figure 1 of DocDB-46577
    float z0 = 0; // z0 parameter of this KinematicLine segment, see Figure 1 of DocDB-46577
    float theta = 0; // theta parameter of this KinematicLine segment, see Figure 1 of DocDB-46577
    float mom = 0; // momentum of this KinematicLine segment, see Figure 1 of DocDB-46577
    float t0 = 0; // time of this KinematicLine segment, see Figure 1 of DocDB-46577
    float d0err = 0; // uncertainty on the d0 parameter of this KinematicLine segment
    float phi0err = 0; // uncertainty on the phi0 parameter of this KinematicLine segment
    float z0err = 0; // uncertainty on the z0 parameter of this KinematicLine segment
    float thetaerr = 0; // uncertainty on the theta parameter of this KinematicLine segment
    float momerr = 0; // uncertainty on the momentum of this KinematicLine segment
    float t0err = 0; // uncertainty on the time of this KinematicLine segment
    void reset() { *this = KinematicLineInfo(); }
  };
}
#endif
