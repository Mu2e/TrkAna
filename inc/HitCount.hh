#ifndef HitCountHH
#define HitCountHH
//
// Struct to count hits in an event
// Dave Brown, LBNL 7/8/2016
namespace mu2e
{
  struct HitCount {
    int nsd = 0; // number of Straw digis
    int nesel = 0; // number of StrawHits flaged as passing energy deposition cuts
    int nrsel = 0; // number of StrawHits flaged as passing radius cuts
    int ntsel = 0; // number of StrawHits flaged as passing  time cuts
    int nbkg = 0; // number of StrawHits flaged as produced by low-energy electrons (Compton electrons)
    void reset() {*this = HitCount(); }
  };
}
#endif
