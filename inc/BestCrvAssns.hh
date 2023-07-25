#include "canvas/Persistency/Common/Assns.h"

#include "Offline/RecoDataProducts/inc/KalSeed.hh"
#include "Offline/RecoDataProducts/inc/CrvCoincidenceCluster.hh"
#include "Offline/MCDataProducts/inc/CrvCoincidenceClusterMC.hh"

namespace mu2e {
  // Assns between a KalSeed and a CrvCoincidenceCluster
  typedef art::Assns<mu2e::KalSeed, mu2e::CrvCoincidenceCluster> BestCrvAssns;
  typedef art::Assns<mu2e::CrvCoincidenceCluster, mu2e::CrvCoincidenceClusterMC> CrvCoincidenceClusterMCAssns;
}
