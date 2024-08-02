//
// SurfaceStep info to summarize energy deposition in a passive element, or passage through a virtual detector
//
#ifndef SurfaceStepInfo_HH
#define SurfaceStepInfo_HH
#include "Offline/DataProducts/inc/SurfaceId.hh"
#include "TrkAna/inc/RootVectors.hh"

namespace mu2e {
  class SurfaceStep;
  struct SurfaceStepInfo {
    SurfaceId sid; // id of the component being traversed
    float time = 1e15;  // time the particle enters this component the WRT MC primary proton (ns)
    float edep = 0; // total energy loss through this detector component (MeV)
    float path = 0; // path length take through this detector component (mm)
    XYZVectorF pos;  // particle position at the middle of this step in Detector Coordinates (mm)
    XYZVectorF mom;  // particle momentum at the start of this step (MeV)
    SurfaceStepInfo (const SurfaceStep ss); // construct from a SurfaceStep
    SurfaceStepInfo () {}
  };
}
#endif
