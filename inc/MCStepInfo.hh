//
// Struct to record additional MC step information
//
#ifndef MCStepInfo_HH
#define MCStepInfo_HH
#include <vector>
#include "TrkAna/inc/RootVectors.hh"

namespace mu2e {
  struct MCStepInfo {
    int vid=-1; // volume Id or VirtualDetector Id of this step
    int sid=-1; // matching IntersectionInfo SurfaceId
    int iinter=-1; // matching IntersectionInfo index
    float time = 0;  // time of this step WRT MC primary proton (ns)
    float de = 0; // energy deposit through this step (MeV)
    float dp = 0; // momentum magnitude change throw this step (MeV/c)
    bool early = false;
    bool late = false; // flag if this is the earliest or latest step
    XYZVectorF mom; // particle momentum at the start of this step
    XYZVectorF pos;  // particle position at the start of this step
    void reset() {*this = MCStepInfo(); }
    bool valid() { return vid>=0; }
  };

  struct MCStepSummaryInfo {
    unsigned nsteps = 0; // number of indivdual steps
    float ftime = 1e15;  // time of the first step WRT MC primary proton (ns)
    float ltime = -1e15;  // time of the last step WRT MC primary proton (ns)
    float de = 0; // sum energy deposit through these steps (MeV)
    float dp = 0; // sum momentum magnitude change through this step (MeV/c)
    void reset() {*this = MCStepSummaryInfo(); }

    void addStep(MCStepInfo const& mcsi) {
      nsteps++;
      ftime = std::min(ftime,mcsi.time);
      ltime = std::max(ltime,mcsi.time);
      de += mcsi.de;
      dp += mcsi.dp;
    }
  };
  using MCStepInfos = std::vector<MCStepInfo>;
}
#endif
