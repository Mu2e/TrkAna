#ifndef CaloClusterInfoReco_HH
#define CaloClusterInfoReco_HH

#include "Rtypes.h"
namespace mu2e
{
  struct CaloClusterInfoReco{
    int   nclu  = -1;
    float cposX = -1000.0;
    float cposY = -1000.0;
    float cposZ = -1000.0;
    float cposR = -1000.0;
    float edep = -1000.0;
    float edepErr = -1000.0;
    float time = - 1000.0;
    float timeErr = -1000.0;
    int diskId = -1;

    void reset(){ *this = CaloClusterInfoReco(); }
  };
}


#endif
