#ifndef CrvHitInfoReco_hh
#define CrvHitInfoReco_hh

#include "Offline/DataProducts/inc/GenVector.hh"
#include "Offline/DataProducts/inc/CRVId.hh"
#include "CLHEP/Vector/ThreeVector.h"
#include <vector>
#include <array>
#include "Rtypes.h"

namespace mu2e
{

  struct CrvHitInfoReco   //information about a cluster of CRV coincidence triplets
  {
    Int_t               sectorType =-1;   //CRV sector type
    XYZVectorF          pos; //average position of counters
    Float_t             timeStart = -1; //first hit time
    Float_t             timeEnd = -1;   //last hit time
    Float_t             time = -1; // average hit time
    Float_t             PEs = -1;   //total number of PEs for this cluster
    std::array<Float_t, CRVId::nLayers> PEsPerLayer = {-1};  // PEs per layer for this cluster
    Int_t               nHits = -1;      //number of coincidence hits in this cluster
    Int_t               nLayers = -1;      //number of coincidence layers in this cluster
    Float_t             angle = -999;   //coincidence direction

    CrvHitInfoReco(){}
    CrvHitInfoReco(int sectorType, CLHEP::Hep3Vector hpos, float timeWindowStart, float timeWindowEnd, float timeAvg, float PEs, std::array<float, CRVId::nLayers> PEsPerLayer, int nCoincidenceHits, int nCoincidenceLayers, float coincidenceAngle) :
      sectorType(sectorType),
      pos(hpos),
      timeStart(timeWindowStart),
      timeEnd(timeWindowEnd),
      time(timeAvg),
      PEs(PEs),
      PEsPerLayer(PEsPerLayer),
      nHits(nCoincidenceHits),
      nLayers(nCoincidenceLayers),
      angle(coincidenceAngle)
    {}
  };

  typedef std::vector<CrvHitInfoReco> CrvHitInfoRecoCollection;  //this is the reco vector which will be stored in the main TTree

}
#endif
