//
// TrkFitInfo: generic information about the track fit at a particular Surface
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
    XYZVectorF mom;
    XYZVectorF pos;
    double time;
    float momerr = -1000;  // projected error on the scalar momentum
    bool inbounds = false; // was the intersection within the (literal) surface bounds
    bool gap = false; // was the intersection in a piecewise trajectory gap
    bool early = false; // is this the earliest intersection for this track
    bool late = false; // is this the latest intersection for this track
    int sid = SurfaceIdEnum::unknown; // SurfaceId of the intersected surface, see Offline/KinKalGeom/inc/SurfaceId.hh
    int sindex = 0; // index to the intersected surface (for multi-surface elements like StoppingTarget)
    void reset() { *this = TrkFitInfo(); }
  };
}
#endif
