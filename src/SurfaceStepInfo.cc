#include "TrkAna/inc/SurfaceStepInfo.hh"
#include "Offline/MCDataProducts/inc/SurfaceStep.hh"
namespace mu2e {
  SurfaceStepInfo::SurfaceStepInfo (const SurfaceStep ss) : sid(ss.surfaceId()), time(ss.time()), edep(ss.energyDeposit()),
  path(ss.pathLength()), pos(ss.midPosition()), mom(ss.momentum()){}
}
