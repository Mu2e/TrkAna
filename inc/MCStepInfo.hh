//
// Struct to record additional MC step information
//
#ifndef MCStepInfo_HH
#define MCStepInfo_HH
#include <vector>
namespace mu2e {
  struct MCStepInfo {
    float time = 0;  // time of this step WRT MC primary proton (ns)
    float de = 0; // energy change through this step (MeV)
    float ddir = 0; // momentum direction change through this step (radians)
    XYZVectorF mom; // particle momentum at the start of this step
    XYZVectorF pos;  // particle position at the start of this step
    void reset() {*this = MCStepInfo(); }
  };
  struct MCStepSummaryInfo {
    int nsteps = 0; // number of indivdual steps
    float ftime = 1e15;  // time of the first step WRT MC primary proton (ns)
    float ltime = -1e15;  // time of the last step WRT MC primary proton (ns)
    float de = 0; // sum energy change through these steps (MeV)
    float ddir = 0; // sum momentum direction change through this step (radians)
    void reset() {*this = MCStepSummaryInfo(); }
  };
  using MCStepInfos = std::vector<MCStepInfo>;
}
#endif
