#ifndef TrackSegment_hh_
#define TrackSegment_hh_

#include "TrkAna/inc/TrkFitInfo.hh"

struct TrackSegment {
  TrackSegment(mu2e::TrkFitInfo* trkfit) : trkfit(trkfit) { }

  // Pointers to the data
  mu2e::TrkFitInfo* trkfit = nullptr;

  static bool earliest(const TrackSegment& seg1, const TrackSegment& seg2) {
    return seg1.trkfit->time < seg2.trkfit->time;
  }
};

typedef bool (*TrackSegmentCut)(const TrackSegment& track_seg);
typedef std::vector<TrackSegment> TrackSegments;

#endif
