//
// Struct to describe straw materials on the Kalman fit
//
#ifndef TrkStrawMatInfoHH
#define TrkStrawMatInfoHH
#include "Rtypes.h"
namespace mu2e
{
  struct TrkStrawMatInfo {
    Bool_t active;    // was this material was used in the Kalman fit or not
    Int_t plane, panel, layer, straw; // StrawId fields of the straw
    Float_t doca;    // DOCA between the track fit and the wire
    Float_t tlen;   // length along the helix of the POCA
    Float_t dp;      // momentum (energy) loss induced by this straw's material, including both entry and exit wall and the gas
    Float_t radlen;  // radiation length of this straw's material seen by the track (including angular effects)
    TrkStrawMatInfo() : active(false),
    plane(-1), panel(-1), layer(-1), straw(-1),
    doca(-1000.0), tlen(-1000.0),
    dp(-1000.0), radlen(-1000.0) {}
  };
}
#endif
