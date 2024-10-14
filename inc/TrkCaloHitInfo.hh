//
// TrkCaloHitInfo: an array branch with information on the calorimeter cluster assigned to a track. Example structure: [ trk1_caloHit, trk2_caloHit, ..., trkN_caloHit ]
// original author: Dave Brown (LBNL), Jan 2019
//
#ifndef TrkCaloHitInfo_HH
#define TrkCaloHitInfo_HH
#include "EventNtuple/inc/RootVectors.hh"
namespace mu2e
{
  struct TrkCaloHitInfo {
    bool active = false;   // is this hit used in the track?
    int did = -1; // disk ID
    XYZVectorF poca; // Position of Point Of Closest Approach (POCA)
    XYZVectorF mom; // Track momentum vector at Point Of Closest Approach (POCA)
    float cdepth = -1000.0; // depth along crystal from Point of Closest Approach (POCA) to the SiPM
    float trkdepth = -1000.0; // depth projected along the track
    float dphidot = -1000.0; //  cosine of relative azimuth between momentum and Point of Closest Approach (POCA)
    float doca = -1000.0; // distance of closest approach (DOCA) of this hit
    float dt = -1000.0; // time difference between track and calorimeter [ns]
    float ptoca = -1000.0; // unbiased particle time of closest approach at point of closest approach
    float tocavar = -1000.0; // unbiased variance on time of closest approach
    float tresid = -1000.0; // unbiased time residual
    float tresidmvar= -1000.0; // measurement variance on unbiased time residual
    float tresidpvar= -1000.0; // parameter variance on unbiased time residual
    float ctime = -1000.0; // cluster time [ns] (from CaloCluster reconstruction)
    float ctimeerr = -1000.0; // uncertainty on cluster time [ns]  (from CaloCluster reconstruction)
    float csize = -1000.0; // the size of the cluster (from CaloCluster reconstruction)
    float edep = -1000.0; // energy deposited [MeV/c] (from CaloCluster reconstruction)
    float edeperr = -1000.0;    // uncertainty on energy deposited [MeV/c] (from CaloCluster reconstruction)
    void reset() { *this = TrkCaloHitInfo(); }
  };
}
#endif
