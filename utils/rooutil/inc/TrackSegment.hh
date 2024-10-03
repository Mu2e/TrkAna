#ifndef TrackSegment_hh_
#define TrackSegment_hh_

#include "TrkAna/inc/TrkSegInfo.hh"

struct TrackSegment {
  TrackSegment(mu2e::TrkSegInfo* trkseg) : trkseg(trkseg) { }

  // Pointers to the data
  mu2e::TrkSegInfo* trkseg = nullptr;

  static bool earliest(const TrackSegment& seg1, const TrackSegment& seg2) {
    return seg1.trkseg->time < seg2.trkseg->time;
  }
};

typedef bool (*TrackSegmentCut)(const TrackSegment& track_seg);
typedef std::vector<TrackSegment> TrackSegments;

#endif
