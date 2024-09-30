#ifndef Track_hh_
#define Track_hh_

#include "TrkAna/inc/TrkInfo.hh"
#include "TrkAna/inc/TrkFitInfo.hh"

struct Track {
  Track(mu2e::TrkInfo* trk, std::vector<mu2e::TrkFitInfo>* trkfit) : trk(trk), trkfit(trkfit) { }

  mu2e::TrkInfo* trk = nullptr;
  std::vector<mu2e::TrkFitInfo>* trkfit = nullptr;
};

typedef bool (*TrackCut)(const Track& track);
typedef std::vector<Track> Tracks;

#endif
