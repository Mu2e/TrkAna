#include "TrkAna/inc/CrvHitInfoMC.hh"
#include "CLHEP/Vector/ThreeVector.h"
namespace mu2e {
  CrvHitInfoMC::CrvHitInfoMC(bool valid, int pdgId,
      int primaryPdgId, float primaryE, CLHEP::Hep3Vector primaryPos,
      int parentPdgId, float parentE, CLHEP::Hep3Vector parentPos,
      int gparentPdgId, float gparentE, CLHEP::Hep3Vector gparentPos,
      CLHEP::Hep3Vector pos, float time, float depositedEnergy) :
    valid(valid),
    pdgId(pdgId),
    primaryPdgId(primaryPdgId),
    primaryE(primaryE),
    primary(primaryPos),
    parentPdgId(parentPdgId),
    parentE(parentE),
    parent(parentPos),
    gparentPdgId(gparentPdgId),
    gparentE(gparentE),
    gparent(gparentPos),
    pos(pos),
    time(time),
    depositedEnergy(depositedEnergy)
  {}
}
