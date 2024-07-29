//
// MCStepSummaryInfo: branch to summarize total StepPointMC information in a given location
//
#ifndef MCStepSummaryInfo_HH
#define MCStepSummaryInfo_HH
#include <vector>
#include "TrkAna/inc/RootVectors.hh"

namespace mu2e {
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
}
#endif
