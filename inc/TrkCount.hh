#ifndef TrkCount_HH
#define TrkCount_HH
#include <string>
// root
//
// Struct to count tracks and track-related quantities in an event
// Dave Brown, LBNL 7/8/2016
namespace mu2e
{
  struct TrkCount {
    static const int MAX_COUNTS = 50;
    //    int _ncounts;
    int _counts[MAX_COUNTS]; // number of tracks in collection
    //    int _overlaps[MAX_COUNTS]; // number of shared hits between candidate track and this track

    int _nde = 0; // number of downstreameMinus tracks
    int _nue = 0; // number of upstreameMinus tracks
    int _ndm = 0; // number of downstreammuMinus tracks
    int _ndec = 0; // Number of calo clusters matched to the best dem track.
    int _ndeo = 0; // number of shared hits between primary and next-best track
    int _ndmo = 0; // number of shared hits between primary and muon-fit track
    void reset() { *this = TrkCount(); }
  };
}
#endif
