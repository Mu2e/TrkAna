#ifndef CrvSummaryReco_hh
#define CrvSummaryReco_hh

// CrvSummaryReco: branch that provides a summary of the CRV information

namespace mu2e
{
  struct CrvSummaryReco
  {
    int totalPEs = -1;
    int nHitCounters = -1;
    CrvSummaryReco(){}
    CrvSummaryReco(int totalPEs, int nHitCounters) :
      totalPEs(totalPEs),
      nHitCounters(nHitCounters)
    {}
  };
}
#endif


