//
// Struct describing a single straw hit assigned to a track, for use in TTree diagnostics
//
#ifndef TrkStrawHitInfoHH
#define TrkStrawHitInfoHH
#include "Rtypes.h"
#include "Offline/DataProducts/inc/GenVector.hh"
namespace mu2e
{
  struct TrkStrawHitInfo {
    Bool_t active;   // is this hit used in the track?
    Bool_t dhit;     // is this hit one of a pair in a panel?
    Bool_t dactive;  // is this hit one of a panel pair that are both used in the track
    Int_t plane, panel, layer, straw;  // StrawId fields for the straw hit
    Int_t ambig;     // left-right amibiguity.  This signes the angular momentum of the track WRT the wire
    Int_t driftend; // which end(s) was used in computing the drift
    Float_t tdrift; // drift time
    XYZVectorF poca; // Position of Point Of Closest Approach (POCA)
    Float_t resid;  // residual = Distance Of Closest Approach (DOCA) between the drift cylinder and the track, signed by the track angular momentum WRT the wire
    Float_t residerr;  // error on the residual, including components from the hit, the track, and potentially other effects
    Float_t rdrift, rdrifterr;  // drift radius and error of this hit
    Float_t wdist, werr; // TD- valuedistance along straw from center and error on that
    Float_t trklen;// distance along the helix of the POCA for this hit
    Float_t doca;// DOCA of this hit
    Float_t t0, t0err;  // Estimated time the particle passed the POCA of this hit (and error).  Note this is mass hypothesis dependent
    Float_t ht;    // reconstructed time (including drift time) of this hit
    Float_t hlen;    // length along the straw from the straw center of the POCA
    Float_t wdot;    // dot-product of the track direction at POCA with the wire direction
    Float_t edep;    // reconstructed energy deposition from ADC measurement
    Float_t dx;      // estimated distance through the straw gas traversed by this particle, given the DOCA and track parameters
    TrkStrawHitInfo() : active(false), dhit(false), dactive(false),
    plane(-1), panel(-1), layer(-1), straw(-1), ambig(-1),driftend(-1),
    tdrift(-1000.0),
    resid(-1000.0), residerr(-1000.0), rdrift(-1000.0), rdrifterr(-1000.0),
    wdist(-1000.0), werr(-1000.0),
    trklen(-1000.0),
    doca(-1000.0), t0(-1000.0), t0err(-1000.0),
    ht(-1000.0),  hlen(-1000.0), wdot(-1000.0),
    edep(-1000.0), dx(-1000.0)  {}
  };
}
#endif
