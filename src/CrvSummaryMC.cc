#include "EventNtuple/inc/CrvSummaryMC.hh"
#include "CLHEP/Vector/ThreeVector.h"
namespace mu2e {
  CrvSummaryMC::CrvSummaryMC(double totalEnergyDeposited, double minPathLayer,  double maxPathLayer, int nHitCounters, CLHEP::Hep3Vector ppos, int sectorNumber, int sectorType, int pdgId) :
    totalEnergyDeposited(totalEnergyDeposited),
    minPathLayer(minPathLayer),
    maxPathLayer(maxPathLayer),
    nHitCounters(nHitCounters),
    pos(ppos),
    sectorNumber(sectorNumber),
    sectorType(sectorType),
    pdgId(pdgId)
  {}
}
