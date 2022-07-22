#ifndef HitCountHH
#define HitCountHH
// root
#include "Rtypes.h"
//
// Struct to count hits in an event
// Dave Brown, LBNL 7/8/2016
namespace mu2e
{
  struct HitCount {
    Int_t nsd; // Total number of StrawDigis
    Int_t nesel; // number of StrawHits flaged as passing energy deposition cuts
    Int_t nrsel; // number of StrawHits flaged as passing radius cuts
    Int_t ntsel; // number of StrawHits flaged as passing  time cuts
    Int_t nbkg; // number of StrawHits flaged as produced by low-energy electrons (Compton electrons)
    Int_t ntpk; // number of StrawHits assigned to a time peak
    Int_t ncd, ncrvd; // # calo digis, clusters, and crv digis
    static std::string const& leafnames() {
      static const std::string leaves =
        std::string("nsh/I:nesel/I:nrsel/I:ntsel/I:nbkg/I:ntpk/I:ncd/I:ncrvd/I");
      return leaves;
    }
    void reset() {
      nsd = nesel = nrsel = ntsel = nbkg = ntpk = ncd = ncrvd = 0;
    }
  };
}
#endif
