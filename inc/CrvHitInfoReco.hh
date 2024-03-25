#ifndef CrvHitInfoReco_hh
#define CrvHitInfoReco_hh

#include "TrkAna/inc/RootVectors.hh"
#include "Offline/DataProducts/inc/CRVId.hh"
namespace CLHEP {class Hep3Vector }
#include <vector>
#include <array>

namespace mu2e
{

  struct CrvHitInfoReco   //information about a cluster of CRV coincidence triplets
  {
    int               sectorType =-1;   //CRV sector type
    XYZVectorF          pos; //average position of counters
    float             timeStart = -1; //first hit time
    float             timeEnd = -1;   //last hit time
    float             time = -1; // average hit time
    float             PEs = -1;   //total number of PEs for this cluster
    std::array<float, CRVId::nLayers> PEsPerLayer = {-1};  // PEs per layer for this cluster
    int               nHits = -1;      //number of coincidence hits in this cluster
    int               nLayers = -1;      //number of coincidence layers in this cluster
    float             angle = -999;   //coincidence direction

    CrvHitInfoReco(){}
    CrvHitInfoReco(int sectorType, CLHEP::Hep3Vector hpos, float timeWindowStart, float timeWindowEnd, float timeAvg, float PEs, std::array<float, CRVId::nLayers> PEsPerLayer, int nCoincidenceHits, int nCoincidenceLayers, float coincidenceAngle);
  };
  typedef std::vector<CrvHitInfoReco> CrvHitInfoRecoCollection;  //this is the reco vector which will be stored in the main TTree
}
#endif
