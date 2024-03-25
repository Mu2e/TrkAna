#ifndef CrvHitInfoMC_hh
#define CrvHitInfoMC_hh
namespace CLHEP {class Hep3Vector }
#include <vector>
#include "TrkAna/inc/RootVectors.hh"

namespace mu2e
{
  struct CrvHitInfoMC  //information about the MC track which most likely caused the CRV coincidence triplets
  {
    bool              valid = false;            //was an MC particle found that matches the coincidence triplets?
    int               pdgId = -1;            //PDG ID of this MC particle
    int               primaryPdgId = -1;     //PDG ID of the primary particle of this MC particle (helps to determine whether it was a cosmic ray, etc.)
    float             primaryE = -1;         //energy of the primary particle of this MC particle
    XYZVectorF          primary;   //starting point of the primary particle of this MC particle
    int               parentPdgId = -1;     //PDG ID of the parent particle of this MC particle (helps to determine whether it was a cosmic ray, etc.)
    float             parentE = -1;         //energy of the parent particle of this MC particle
    XYZVectorF          parent;   //starting point of the parent particle of this MC particle
    int               gparentPdgId = -1;     //PDG ID of the gparent particle of this MC particle (helps to determine whether it was a cosmic ray, etc.)
    float             gparentE = -1;         //energy of the gparent particle of this MC particle
    XYZVectorF          gparent;   //starting point of the gparent particle of this MC particle
    XYZVectorF          pos;    //position of the MC particle when it "created" the first StepPointMC
    float             time = -1;             //time of the MC particle when it "created" the first StepPointMC
    float             depositedEnergy = -1;  //total energy deposited for this cluster (not just for this track)
    CrvHitInfoMC(){}
    CrvHitInfoMC(bool valid, int pdgId,
        int primaryPdgId, float primaryE, CLHEP::Hep3Vector primaryPos,
        int parentPdgId, float parentE, CLHEP::Hep3Vector parentPos,
        int gparentPdgId, float gparentE, CLHEP::Hep3Vector gparentPos,
        CLHEP::Hep3Vector pos, float time, float depositedEnergy);
  };
  typedef std::vector<CrvHitInfoMC>   CrvHitInfoMCCollection;    //this is the MC vector which will be stored in the main TTree
}
#endif
