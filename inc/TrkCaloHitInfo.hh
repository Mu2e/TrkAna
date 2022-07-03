//
// Struct describing a calorimeter cluster assigned to a track, for use in TTree diagnostics
// original author: Dave Brown (LBNL), Jan 2019
//
#ifndef TrkCaloHitInfo_HH
#define TrkCaloHitInfo_HH
#include "Rtypes.h"
#include "Offline/DataProducts/inc/GenVector.hh"
namespace mu2e
{
  struct TrkCaloHitInfo {
    Int_t active;   // is this hit used in the track?
    Int_t did; // disk ID
    XYZVectorF poca; // Position of Point Of Closest Approach (POCA)
    XYZVectorF mom; // Track momentum vector at Point Of Closest Approach (POCA)
    Float_t cdepth;    // depth at POCA
    Float_t doca; // DOCA of this hit
    Float_t dt, toca, tocavar; // dt and TOCA of this hit
    Float_t tresid, tresidmvar, tresidpvar; // unbiased time residual and associated measurement and parameter variances
    Float_t edep;    // reconstructed crystal energy deposition
    TrkCaloHitInfo() : active(false),did(-1),
    cdepth(-1000.0),
    doca(-1000.0), dt(-1000.0), toca(-1000.0), tocavar(-1000.0),
    tresid(-1000.0), tresidmvar(-1000.0), tresidpvar(-1000.0),
    edep(-1000.0)  {}
    void reset() { *this = TrkCaloHitInfo(); }
  };
}
#endif
