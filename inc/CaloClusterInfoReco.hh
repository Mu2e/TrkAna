#ifndef CaloClusterInfoReco_HH
#define CaloClusterInfoReco_HH

#include <vector>
#include "Rtypes.h"
#include "Offline/DataProducts/inc/GenVector.hh"

namespace mu2e
{
  struct CaloClusterInfoReco{
    int   nclu  = -1;
    XYZVectorF cpos;
    float edep = -1000.0;
    float edepErr = -1000.0;
    float time = - 1000.0;
    float timeErr = -1000.0;
    int diskId = -1;
    int ncry =-1;
    bool isSplit;

    std::vector<int> cryId;
    std::vector<float> cryEdep;
    std::vector<float> cryEdepErr;
    std::vector<float> cryTime;
    std::vector<float> cryTimeErr;
    std::vector<CLHEP::Hep3Vector> cryPos;
    
    void reset(){ *this = CaloClusterInfoReco(); }
  };
}



#endif
