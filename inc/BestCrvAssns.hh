#include "canvas/Persistency/Common/Assns.h"

#include "Offline/RecoDataProducts/inc/KalSeed.hh"
#include "Offline/RecoDataProducts/inc/CrvCoincidenceCluster.hh"

namespace mu2e {
  // Assns between a KalSeed and a CrvCoincidenceCluster
  typedef art::Assns<mu2e::KalSeed, mu2e::CrvCoincidenceCluster> BestCrvAssns;
}
