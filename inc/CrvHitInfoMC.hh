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
    Bool_t              _valid;            //was an MC particle found that matches the coincidence triplets?
    Int_t               _pdgId;            //PDG ID of this MC particle
    Int_t               _primaryPdgId;     //PDG ID of the primary particle of this MC particle (helps to determine whether it was a cosmic ray, etc.)
    Float_t             _primaryE;         //energy of the primary particle of this MC particle
    XYZVectorF  _primary;   //starting point of the primary particle of this MC particle

    Int_t               _parentPdgId;     //PDG ID of the parent particle of this MC particle (helps to determine whether it was a cosmic ray, etc.)
    Float_t             _parentE;         //energy of the parent particle of this MC particle
    XYZVectorF _parent;   //starting point of the parent particle of this MC particle

    Int_t               _gparentPdgId;     //PDG ID of the gparent particle of this MC particle (helps to determine whether it was a cosmic ray, etc.)
    Float_t             _gparentE;         //energy of the gparent particle of this MC particle
    XYZVectorF _gparent;   //starting point of the gparent particle of this MC particle

    XYZVectorF _pos;//position of the MC particle when it "created" the first StepPointMC
    Float_t             _time;             //time of the MC particle when it "created" the first StepPointMC
    Float_t             _depositedEnergy;  //total energy deposited for this cluster (not just for this track)
    CrvHitInfoMC(bool valid, int pdgId,
              int primaryPdgId, float primaryE, CLHEP::Hep3Vector primaryPos,
              int parentPdgId, float parentE, CLHEP::Hep3Vector parentPos,
              int gparentPdgId, float gparentE, CLHEP::Hep3Vector gparentPos,
              CLHEP::Hep3Vector pos, float time, float depositedEnergy) :
              _valid(valid),
              _pdgId(pdgId),
              _primaryPdgId(primaryPdgId),
              _primaryE(primaryE),
              _primary(primaryPos),
              _parentPdgId(parentPdgId),
              _parentE(parentE),
              _parent(parentPos),
              _gparentPdgId(gparentPdgId),
              _gparentE(gparentE),
              _gparent(gparentPos),
              _pos(pos),
              _time(time),
              _depositedEnergy(depositedEnergy)
              {}
    CrvHitInfoMC() :
              _valid(false),
              _pdgId(0),
              _primaryPdgId(0),
              _primaryE(0),
              _parentPdgId(0),
              _parentE(0),
              _gparentPdgId(0),
              _gparentE(0),
              _time(0),
              _depositedEnergy(0)
              {}
  };

  typedef std::vector<CrvHitInfoMC>   CrvHitInfoMCCollection;    //this is the MC vector which will be stored in the main TTree

}
#endif
