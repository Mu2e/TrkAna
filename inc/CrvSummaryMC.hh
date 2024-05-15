#ifndef CrvSummaryMC_hh
#define CrvSummaryMC_hh

#include "Rtypes.h"
#include "Offline/DataProducts/inc/GenVector.hh"
namespace mu2e
{
  struct CrvSummaryMC
  {
    Double_t   totalEnergyDeposited = -1;
    Double_t   minPathLayer = -1;
    Double_t   maxPathLayer = -1;
    Int_t      nHitCounters = -1;
    XYZVectorF pos;   //position of the first MC particle in CRV
    Int_t      sectorNumber = -1; //CRV sector number of the first MC particle in CR
    Int_t      sectorType = -1;   //CRV sector type of the first MC particle in CRV
    Int_t      pdgId = -1;           //PDG ID of the first MC particle in CRV

    CrvSummaryMC(){}
    CrvSummaryMC(double totalEnergyDeposited, double minPathLayer,  double maxPathLayer, int nHitCounters, CLHEP::Hep3Vector ppos, int sectorNumber, int sectorType, int pdgId) :
      totalEnergyDeposited(totalEnergyDeposited),
      minPathLayer(minPathLayer),
      maxPathLayer(maxPathLayer),
      nHitCounters(nHitCounters),
      pos(ppos),
      sectorNumber(sectorNumber),
      sectorType(sectorType),
      pdgId(pdgId)
    {}
  };
}
#endif
