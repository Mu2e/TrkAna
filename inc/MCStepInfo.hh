//
// Struct to record additional MC step information
//
#ifndef MCStepInfo_HH
#define MCStepInfo_HH
#include <vector>
namespace mu2e {
  struct MCStepInfo {
    unsigned vid=0; // volume ID of this step
    float time = 0;  // time of this step WRT MC primary proton (ns)
    float de = 0; // energy deposit through this step (MeV)
    float dp = 0; // momentum magnitude change throw this step (MeV/c)
    XYZVectorF mom; // particle momentum at the start of this step
    XYZVectorF pos;  // particle position at the start of this step
    void reset() {*this = MCStepInfo(); }
  };
  struct MCStepSummaryInfo {
    int nsteps = 0; // number of indivdual steps
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
