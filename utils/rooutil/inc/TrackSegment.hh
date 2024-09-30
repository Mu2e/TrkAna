#ifndef TrackSegment_hh_
#define TrackSegment_hh_

#include "TrkAna/inc/TrkFitInfo.hh"

struct TrackSegment {
  TrackSegment(mu2e::TrkFitInfo* trkfit) : trkfit(trkfit) { }

  // Pointers to the data
  mu2e::TrkFitInfo* trkfit = nullptr;
};

typedef bool (*TrackSegmentCut)(const TrackSegment& track_seg);
typedef std::vector<TrackSegment> TrackSegments;

#endif
