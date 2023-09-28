#ifndef CrvHitInfoMC_hh
#define CrvHitInfoMC_hh

#include "CLHEP/Vector/ThreeVector.h"
#include <vector>
#include "Rtypes.h"
#include "Offline/DataProducts/inc/GenVector.hh"

namespace mu2e
{
  struct CrvHitInfoMC  //information about the MC track which most likely caused the CRV coincidence triplets
  {
    Bool_t              valid = false;            //was an MC particle found that matches the coincidence triplets?
    Int_t               pdgId = -1;            //PDG ID of this MC particle
    Int_t               primaryPdgId = -1;     //PDG ID of the primary particle of this MC particle (helps to determine whether it was a cosmic ray, etc.)
    Float_t             primaryE = -1;         //energy of the primary particle of this MC particle
    XYZVectorF          primary;   //starting point of the primary particle of this MC particle
    Int_t               parentPdgId = -1;     //PDG ID of the parent particle of this MC particle (helps to determine whether it was a cosmic ray, etc.)
    Float_t             parentE = -1;         //energy of the parent particle of this MC particle
    XYZVectorF          parent;   //starting point of the parent particle of this MC particle
    Int_t               gparentPdgId = -1;     //PDG ID of the gparent particle of this MC particle (helps to determine whether it was a cosmic ray, etc.)
    Float_t             gparentE = -1;         //energy of the gparent particle of this MC particle
    XYZVectorF          gparent;   //starting point of the gparent particle of this MC particle
    XYZVectorF          pos;    //position of the MC particle when it "created" the first StepPointMC
    Float_t             time = -1;             //time of the MC particle when it "created" the first StepPointMC
    Float_t             depositedEnergy = -1;  //total energy deposited for this cluster (not just for this track)
    CrvHitInfoMC(){}
    CrvHitInfoMC(bool valid, int pdgId,
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
  };

  typedef std::vector<CrvHitInfoMC>   CrvHitInfoMCCollection;    //this is the MC vector which will be stored in the main TTree

}
#endif
