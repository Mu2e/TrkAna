#ifndef CrvPlaneInfoMC_hh
#define CrvPlaneInfoMC_hh

#include "CLHEP/Vector/ThreeVector.h"
#include <vector>
#include "Rtypes.h"

namespace mu2e
{
  struct CrvPlaneInfoMC  //information about the point where the MC trajectory crosses the xz plane of CRV-T
  {
    Int_t    pdgId = -1;            //PDG ID of this MC particle
    Int_t    primaryPdgId = -1;     //PDG ID of the primary particle of this MC particle
    Float_t  primaryE = -1;         //energy of the primary particle of this MC particle
    XYZVectorF  primary;           //starting point of the primary particle of this MC particle
    XYZVectorF pos;               //position of the MC particle when it crosses the xz plane of CRV-T
    XYZVectorF dir;             //direction of the MC particle when it crosses the xz plane of CRV-T
    Float_t  time = -1;             //time of the MC particle when it crosses the xz plane of CRV-T
    Float_t  kineticEnergy = -1;    //time of the MC particle when it crosses the xz plane of CRV-T
    Int_t    dataSource = -1;       //temporary variable; will be removed (1...data from stepPointMCs, 2...data from trajectory extrapolation)
    CrvPlaneInfoMC(){}
    CrvPlaneInfoMC(int pdgId, int primaryPdgId, float primaryE, CLHEP::Hep3Vector primaryPos,
        CLHEP::Hep3Vector ppos, CLHEP::Hep3Vector pdir, float time, float kineticEnergy, int dataSource) :
      pdgId(pdgId),
      primaryPdgId(primaryPdgId),
      primaryE(primaryE),
      primary(primaryPos),
      pos(ppos),
      dir(pdir),
      time(time),
      kineticEnergy(kineticEnergy),
      dataSource(dataSource)
    {}
  };

  typedef std::vector<CrvPlaneInfoMC>   CrvPlaneInfoMCCollection;    //this is the MC vector which will be stored in the main TTree

}
#endif


