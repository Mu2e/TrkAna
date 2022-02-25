//
// Struct describing MC truth for calorimeter cluster
// original author: Dave Brown (LBNL), Jan 2019
//
#ifndef CaloClusterInfoMC_HH
#define CaloClusterInfoMC_HH
#include "Rtypes.h"
#include "Offline/DataProducts/inc/GenVector.hh"
#include "Offline/MCDataProducts/inc/MCRelationship.hh"
namespace mu2e
{
  struct CaloClusterInfoMC {
    Int_t nsim; // # of sim particles associated with this cluster
    Float_t etot; // total true energy from all particles in this cluster
    Float_t tavg; // average time over all particles
    Float_t eprimary; // primary particle true energy in this cluster
    Float_t tprimary; // primary particle average time
    MCRelationship prel; // relationship of the cluster primary particle to the event primary
    CaloClusterInfoMC() : nsim(0), etot(0.0), tavg(0.0), eprimary(0.0), tprimary(0.0){}
    void reset() { *this = CaloClusterInfoMC(); }
  };
}
#endif
