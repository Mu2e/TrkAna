//
// TrkFitInfo: an array of array branch that contains track fit results at particular Surfaces. Example structure: [ [trk1_surfA, trk1_surfB, ...], [trk2_surf_A, trk2_surfC], ... [ trkN_surfB, trkN_surfC] ]
// All momenta are in units of MeV/c, time in nsec WRT when the proton bunch pulse peak hits the production target,
// positions are in mm WRT the center of the tracker.
// Dave Brown (LBNL)
//
#ifndef TrkFitInfo_HH
#define TrkFitInfo_HH
#include "TrkAna/inc/RootVectors.hh"
#include "Offline/DataProducts/inc/SurfaceId.hh"
namespace mu2e
{
  struct TrkFitInfo {
    XYZVectorF mom = XYZVectorF(); // momentum of the fit at this Surface
    XYZVectorF pos = XYZVectorF(); // position of the fit at this Surface
    double time = 0.0; // time of the fit at this Surface
    float momerr = -1000;  // projected error on the scalar momentum
    bool inbounds = false; // was the intersection within the (literal) surface bounds?
    bool gap = false; // was the intersection in a piecewise trajectory gap?
    bool early = false; // is this the earliest intersection for this track?
    bool late = false; // is this the latest intersection for this track?
    int sid = SurfaceIdEnum::unknown; // SurfaceId of the intersected surface, see Offline/KinKalGeom/inc/SurfaceId.hh for definitions
    int sindex = 0; // index to the intersected surface (for multi-surface elements like StoppingTarget)
    void reset() { *this = TrkFitInfo(); }
  };
}
#endif
