#include "TrkAna/inc/CrvHitInfoReco.hh"
#include "CLHEP/Vector/ThreeVector.h"
namespace mu2e {
  CrvHitInfoReco::CrvHitInfoReco(int sectorType, CLHEP::Hep3Vector hpos, float timeWindowStart, float timeWindowEnd, float timeAvg, float PEs, std::array<float, CRVId::nLayers> PEsPerLayer, int nCoincidenceHits, int nCoincidenceLayers, float coincidenceAngle) :
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
}
