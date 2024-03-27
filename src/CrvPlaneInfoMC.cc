#include "TrkAna/inc/CrvPlaneInfoMC.hh"
#include "CLHEP/Vector/ThreeVector.h"
namespace mu2e {
  CrvPlaneInfoMC::CrvPlaneInfoMC(int pdgId, int primaryPdgId, float primaryE, CLHEP::Hep3Vector primaryPos,
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
}
