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
    bool active = false;   // is this hit used in the track?
    int did = -1; // disk ID
    XYZVectorF poca; // Position of Point Of Closest Approach (POCA)
    XYZVectorF mom; // Track momentum vector at Point Of Closest Approach (POCA)
    float cdepth = -1000.0; // depth along crystal from POCA to the SiPM
    float trkdepth = -1000.0; // depth projected along the track
    float dphidot = -1000.0; //  cosine of relative azimuth between momentum and POCA
    float doca = -1000.0; // DOCA of this hit
    float dt = -1000.0;
    float ptoca = -1000.0;
    float tocavar = -1000.0; // dt and TOCA of this hit
    float tresid = -1000.0;
    float tresidmvar= -1000.0;
    float tresidpvar= -1000.0; // unbiased time residual and associated measurement and parameter variances
    float ctime = -1000.0;
    float ctimeerr = -1000.0;
    float csize = -1000.0;
    float edep = -1000.0;
    float edeperr = -1000.0;
    float cposX = -1000.0;
    float cposY = -1000.0;
    float cposZ = -1000.0;
    float cposR = -1000.0; // reconstructed cluster properties
    void reset() { *this = TrkCaloHitInfo(); }
  };
}
#endif
