//
// struct to place variables that are used for TrkPID calculation
//
#ifndef TrkPIDInfo_HH
#define TrkPIDInfo_HH
#include "Offline/RecoDataProducts/inc/TrkCaloHitPID.hh"
namespace mu2e
{
// general information about a track
  struct TrkPIDInfo {
    float _tchpvars[TrkCaloHitPID::n_vars] = { -1000.0 };
    float _mvaout = -1;
    int _mvastat = -1;
// extrapolation radii to the disks; front and back
    float _diskfrad[2] = { -1000.0 }, _diskbrad[2] = { -1000.0 };

    // eventually add dE/dx PID FIXME!
    void reset() { *this = TrkPIDInfo(); }
  };
}
#endif
