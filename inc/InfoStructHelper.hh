//
// Class for help filling Info structs
// Original author: A. Edmonds (November 2018)
//
#ifndef TrkAna_InfoStructHelper_hh
#define TrkAna_InfoStructHelper_hh
#include "Offline/RecoDataProducts/inc/StrawHitIndex.hh"
#include "Offline/RecoDataProducts/inc/KalSeed.hh"
#include "Offline/RecoDataProducts/inc/StrawHitFlag.hh"
#include "Offline/RecoDataProducts/inc/TrkQual.hh"
#include "Offline/RecoDataProducts/inc/RecoCount.hh"
#include "Offline/RecoDataProducts/inc/HelixSeed.hh"
#include "Offline/RecoDataProducts/inc/CrvCoincidenceCluster.hh"

#include "Offline/BFieldGeom/inc/BFieldManager.hh"
#include "Offline/GeometryService/inc/DetectorSystem.hh"
#include "Offline/GeometryService/inc/GeomHandle.hh"
#include "Offline/CalorimeterGeom/inc/DiskCalorimeter.hh"

#include "TrkAna/inc/HitCount.hh"
#include "TrkAna/inc/TrkInfo.hh"
#include "TrkAna/inc/TrkStrawHitInfo.hh"
#include "TrkAna/inc/TrkStrawMatInfo.hh"
#include "TrkAna/inc/TrkCaloHitInfo.hh"
#include "TrkAna/inc/TrkQualInfo.hh"
#include "TrkAna/inc/TrkPIDInfo.hh"
#include "TrkAna/inc/HelixInfo.hh"
#include "Offline/CRVAnalysis/inc/CrvHitInfoReco.hh"

#include <vector>
#include <functional>
namespace mu2e {
  class InfoStructHelper {

  private:
    double _bz0;

  public:
    InfoStructHelper() {}

    void updateSubRun() {
      mu2e::GeomHandle<mu2e::BFieldManager> bfmgr;
      mu2e::GeomHandle<mu2e::DetectorSystem> det;
      CLHEP::Hep3Vector vpoint_mu2e = det->toMu2e(CLHEP::Hep3Vector(0.0,0.0,0.0));
      _bz0 = bfmgr->getBField(vpoint_mu2e).z();
    }

    void fillHitCount(const StrawHitFlagCollection& flags, HitCount& hitcount);
    void fillHitCount(RecoCount const& nrec, HitCount& hitcount);

    void fillTrkInfo(const KalSeed& kseed,TrkInfo& trkinfo);
    void fillTrkFitInfo(const KalSeed& kseed,TrkFitInfo& trkfitinfo, const XYZVectorF& pos);
    void fillTrkInfoHits(const KalSeed& kseed,TrkInfo& trkinfo);
    void fillTrkInfoStraws(const KalSeed& kseed,TrkInfo& trkinfo);

    void fillHitInfo(const KalSeed& kseed, std::vector<TrkStrawHitInfo>& tshinfos );
    void fillMatInfo(const KalSeed& kseed, std::vector<TrkStrawMatInfo>& tminfos );
    void fillCaloHitInfo(const KalSeed& kseed, TrkCaloHitInfo& tchinfo );
    void fillTrkQualInfo(const TrkQual& tqual, TrkQualInfo& trkqualInfo);
    void fillTrkPIDInfo(const TrkCaloHitPID& tchp, const KalSeed& kseed, TrkPIDInfo& trkpidInfo);
    void fillHelixInfo(art::Ptr<HelixSeed> const& hptr, HelixInfo& hinfo);
    void fillCrvHitInfo(art::Ptr<CrvCoincidenceCluster> const& crvCoinc, CrvHitInfoReco& crvHitInfo);
  };
}

#endif
