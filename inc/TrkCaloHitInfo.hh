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
    Float_t trklen;	// distance along the helix of the POCA for this hit
    Float_t clen;    // length along the crystal from the front face
    Float_t doca;	// DOCA of this hit
    Float_t t0, t0err;  // Estimated time the particle passed the POCA of this hit (and error).  Note this is mass hypothesis dependent
    Float_t ct, cterr;    // reconstructed time (including propagation time)
    Float_t edep;    // reconstructed crystal energy deposition
    TrkCaloHitInfo() : active(false),did(-1),
    trklen(-1000.0), clen(-1000.0),
    doca(-1000.0), t0(-1000.0), t0err(-1000.0),
    ct(-1000.0), cterr(-1000.0), edep(-1000.0)  {}
    void reset() { *this = TrkCaloHitInfo(); }
  };
}
#endif
