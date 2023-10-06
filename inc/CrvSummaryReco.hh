#ifndef CrvSummaryReco_hh
#define CrvSummaryReco_hh

#include "Rtypes.h"

namespace mu2e
{
  struct CrvSummaryReco
  {
    Int_t totalPEs = -1;
    Int_t nHitCounters = -1;
    CrvSummaryReco(){}
    CrvSummaryReco(int totalPEs, int nHitCounters) :
      totalPEs(totalPEs),
      nHitCounters(nHitCounters)
    {}
  };
}
#endif


