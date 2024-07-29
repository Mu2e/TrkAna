#ifndef CrvSummaryMC_hh
#define CrvSummaryMC_hh

// CrvSummaryMC: branch that provides a summary of the CRV MC true information

#include "TrkAna/inc/RootVectors.hh"
namespace CLHEP {class Hep3Vector; }
namespace mu2e
{
  struct CrvSummaryMC
  {
    double   totalEnergyDeposited = -1;
    double   minPathLayer = -1;
    double   maxPathLayer = -1;
    int      nHitCounters = -1;
    XYZVectorF pos;   //position of the first MC particle in CRV
    int      sectorNumber = -1; //CRV sector number of the first MC particle in CR
    int      sectorType = -1;   //CRV sector type of the first MC particle in CRV
    int      pdgId = -1;           //PDG ID of the first MC particle in CRV

    CrvSummaryMC(){}
    CrvSummaryMC(double totalEnergyDeposited, double minPathLayer,  double maxPathLayer, int nHitCounters, CLHEP::Hep3Vector ppos, int sectorNumber, int sectorType, int pdgId) ;
  };
}
#endif
