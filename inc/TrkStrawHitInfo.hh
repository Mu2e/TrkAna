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
    Int_t plane, panel, layer, straw;  // StrawId fields for the straw hit
    Int_t state;     // hit state, including activity and left-right ambiguity
    Int_t algo; // updater algorithm last used on this hit
    Int_t driftend; // which end(s) was used in computing the drift
    Float_t edep;        // reco energy deposition
    Float_t htime;   // raw hit time
    Float_t wdist;       // raw hit U position
    Float_t werr;    // raw hit U position error estimate
    Float_t ptoca;    // reference particle time of closest approach (TOCA)
    Float_t wdoca, wdocavar;   // reference (biased) DOCA from the track to the wire, signed by the angular momentum WRT the wire and the measurement end (and variance)
    Float_t wdt, wtocavar;   // reference (biased) time difference (and variance) at POCA
    Float_t doca, docavar; // unbiaed DOCA (and variance)
    Float_t dt, tocavar;   // fit (unbiased) dt and variance
    Float_t upos; // POCA position along the straw WRT the straw middle
    Float_t tresid, tresidmvar, tresidpvar; // unbiased time residual and associated measurement and parameter variances
    Float_t dresid, dresidmvar, dresidpvar; // unbiased distance residual and associated measurement and parameter variances
    // not sure if we still want these
    Float_t wdot;
    XYZVectorF poca;
    bool dhit, dactive;

    TrkStrawHitInfo() : plane(-1), panel(-1), layer(-1), straw(-1), state(-10),driftend(-1),
    wdoca(0), wdocavar(0), wdt(0), wtocavar(0),
    doca(0.0), docavar(0), dt(0), tocavar(0),
    upos(0),
    tresid(0), tresidmvar(0), tresidpvar(0),
    dresid(0), dresidmvar(0), dresidpvar(0),
    wdot(0), dhit(false), dactive(false) {}
  };
}
#endif
