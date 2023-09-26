#include "TrkAna/inc/CrvInfoHelper.hh"

#include "Offline/CosmicRayShieldGeom/inc/CosmicRayShield.hh"
#include "Offline/CRVConditions/inc/CRVDigitizationPeriod.hh"
#include "Offline/GeometryService/inc/DetectorSystem.hh"
#include "Offline/GeometryService/inc/GeomHandle.hh"
#include "Offline/GeometryService/inc/GeometryService.hh"
#include "Offline/MCDataProducts/inc/CrvCoincidenceClusterMC.hh"
#include "Offline/MCDataProducts/inc/CrvDigiMC.hh"
#include "Offline/MCDataProducts/inc/CrvStep.hh"
#include "Offline/MCDataProducts/inc/MCTrajectory.hh"
#include "Offline/RecoDataProducts/inc/CrvCoincidenceCluster.hh"
#include "Offline/RecoDataProducts/inc/CrvDigi.hh"
#include "Offline/RecoDataProducts/inc/CrvRecoPulse.hh"
#include "Offline/DataProducts/inc/PDGCode.hh"
#include "art/Framework/Principal/Handle.h"
#include "Offline/CRVResponse/inc/CrvMCHelper.hh"
#include "Offline/CRVReco/inc/CrvHelper.hh"

namespace mu2e
{
  void CrvInfoHelper::FillCrvHitInfoCollections(
      art::Handle<CrvCoincidenceClusterCollection> const& crvCoincidences,
      art::Handle<CrvCoincidenceClusterMCCollection> const& crvCoincidencesMC,
      art::Handle<CrvRecoPulseCollection> const& crvRecoPulses,
      art::Handle<CrvStepCollection> const& crvSteps,
      art::Handle<MCTrajectoryCollection> const& mcTrajectories,
      CrvHitInfoRecoCollection &recoInfo, CrvHitInfoMCCollection &MCInfo,
      CrvSummaryReco &recoSummary, CrvSummaryMC &MCSummary,
      CrvPlaneInfoMCCollection &MCInfoPlane, double crvPlaneY) {
    GeomHandle<CosmicRayShield> CRS;
    if(!crvCoincidences.isValid()) return;
    size_t nClusters=crvCoincidences->size();
    for(size_t i=0; i<nClusters; i++)
    {
      const CrvCoincidenceCluster &cluster = crvCoincidences->at(i);

      //fill the Reco collection
      recoInfo.emplace_back(cluster.GetCrvSectorType(), cluster.GetAvgCounterPos(),
          cluster.GetStartTime(), cluster.GetEndTime(),
          cluster.GetPEs(), cluster.GetCrvRecoPulses().size(),
          cluster.GetLayers().size(), cluster.GetSlope());
    }

    if(!crvRecoPulses.isValid()) return;
    size_t nRecoPulses=crvRecoPulses->size();
    recoSummary._totalPEs=0;
    std::set<CRSScintillatorBarIndex> counters;
    for(size_t i=0; i<nRecoPulses; i++)
    {
      recoSummary._totalPEs+=crvRecoPulses->at(i).GetPEs();
      counters.insert(crvRecoPulses->at(i).GetScintillatorBarIndex());
    }
    recoSummary._nHitCounters=counters.size();


    //fill the MC collection
    if(crvCoincidencesMC.isValid())
    {
      size_t nClustersMC=crvCoincidencesMC->size();
      if(nClusters!=nClustersMC) std::cout<<"The number of MC and reco CRV coincidence clusters does not match!"<<std::endl;
      for(size_t i=0; i<nClustersMC; i++)
      {
        const CrvCoincidenceClusterMC &clusterMC = crvCoincidencesMC->at(i);
        if(clusterMC.HasMCInfo())
        {
          const art::Ptr<SimParticle> &simParticle = clusterMC.GetMostLikelySimParticle();
          const art::Ptr<SimParticle> &primaryParticle = FindPrimaryParticle(simParticle);
          const art::Ptr<SimParticle> &parentParticle  = FindParentParticle(simParticle);
          const art::Ptr<SimParticle> &gparentParticle = FindGParentParticle(simParticle);
          MCInfo.emplace_back(true,
              simParticle->pdgId(),
              primaryParticle->pdgId(), primaryParticle->startMomentum().e() - primaryParticle->startMomentum().m(), primaryParticle->startPosition(),
              parentParticle->pdgId(),  parentParticle->startMomentum().e()  - parentParticle->startMomentum().m(),  parentParticle->startPosition(),
              gparentParticle->pdgId(), gparentParticle->startMomentum().e() - gparentParticle->startMomentum().m(), gparentParticle->startPosition(),
              clusterMC.GetEarliestHitPos(),
              clusterMC.GetEarliestHitTime(),
              clusterMC.GetTotalEnergyDeposited());
        }
        else MCInfo.emplace_back();
      }
    }

    MCSummary = {};
    if(crvSteps.isValid())
    {
      size_t nSteps=crvSteps->size();
      MCSummary._totalEnergyDeposited=0;
      std::set<CRSScintillatorBarIndex> counters;
      double totalStep[] = {0, 0, 0, 0};
      for(size_t i=0; i<nSteps; i++){
        MCSummary._totalEnergyDeposited+=crvSteps->at(i).visibleEDep();
        counters.insert(crvSteps->at(i).barIndex());
        const CRSScintillatorBarId &CRVCounterId = CRS->getBar(crvSteps->at(i).barIndex()).id();
        int layer = CRVCounterId.getLayerNumber();
        int pdgId = crvSteps->at(i).simParticle()->pdgId();
        if(abs(pdgId)==PDGCode::mu_minus)
          totalStep[layer] = totalStep[layer] + crvSteps->at(i).pathLength();

        // Save info from the first step in the CRV
        if(i==0){
          CLHEP::Hep3Vector CrvPos = crvSteps->at(i).startPosition();
          MCSummary._x = CrvPos.x();
          MCSummary._y = CrvPos.y();
          MCSummary._z = CrvPos.z();
          int sectorNumber = CRVCounterId.getShieldNumber();
          MCSummary._crvSectorNumber = sectorNumber;
          MCSummary._crvSectorType = CRS->getCRSScintillatorShield(sectorNumber).getSectorType();
          MCSummary._pdgId = pdgId;
        }
      }

      MCSummary._nHitCounters=counters.size();
      MCSummary._minPathLayer=*std::min_element(totalStep,totalStep+4);
      MCSummary._maxPathLayer=*std::max_element(totalStep,totalStep+4);
    }

    //locate points where the cosmic MC trajectories cross the xz plane of CRV-T
    if(mcTrajectories.isValid())
    {
      for(auto trajectoryIter=mcTrajectories->begin(); trajectoryIter!=mcTrajectories->end(); trajectoryIter++)
      {
        const art::Ptr<SimParticle> &trajectorySimParticle = trajectoryIter->first;
        if(abs(trajectorySimParticle->pdgId())!=PDGCode::mu_minus) continue;
        const art::Ptr<SimParticle> &trajectoryPrimaryParticle = FindPrimaryParticle(trajectorySimParticle);
        GenId genId = trajectoryPrimaryParticle->genParticle()->generatorId();
        if(genId==GenId::cosmicToy || genId==GenId::cosmicDYB || genId==GenId::cosmic || genId==GenId::cosmicCRY)
        {
          const std::vector<MCTrajectoryPoint> &points = trajectoryIter->second.points();
          if(points.size()<1) continue;
          CLHEP::Hep3Vector previousPos=points[0].pos();
          for(size_t i=1; i<points.size(); i++)
          {
            CLHEP::Hep3Vector pos=points[i].pos();
            if((previousPos.y()>crvPlaneY && pos.y()<=crvPlaneY) || (previousPos.y()<crvPlaneY && pos.y()>=crvPlaneY))
            {
              double fraction=(crvPlaneY-pos.y())/(previousPos.y()-pos.y());
              CLHEP::Hep3Vector planePos=fraction*(previousPos-pos)+pos;
              CLHEP::Hep3Vector planeDir=(pos-previousPos).unit();
              double planeTime=fraction*(points[i-1].t()-points[i].t())+points[i].t();
              double planeKineticEnergy=fraction*(points[i-1].kineticEnergy()-points[i].kineticEnergy())+points[i].kineticEnergy();
              MCInfoPlane.emplace_back(trajectorySimParticle->pdgId(),
                  trajectoryPrimaryParticle->pdgId(),
                  trajectoryPrimaryParticle->startMomentum().e(),
                  trajectoryPrimaryParticle->startPosition(),
                  planePos,
                  planeDir,
                  planeTime,
                  planeKineticEnergy,
                  0);  //unused
            }
            previousPos=pos;
          }
        }
      }
    }

  }//FillCrvInfoStructure


  void CrvInfoHelper::FillCrvPulseInfoCollections (
      art::Handle<CrvRecoPulseCollection> const& crvRecoPulses,
      art::Handle<CrvDigiMCCollection> const& crvDigiMCs,
      art::Handle<CrvDigiCollection> const& crvDigis,
      CrvPulseInfoRecoCollection &recoInfo, CrvHitInfoMCCollection &MCInfo, CrvWaveformInfoCollection &waveformInfo){


    if(!crvRecoPulses.isValid()) return;

    GeomHandle<CosmicRayShield> CRS;

    // Create SiPM map to extract sequantial SiPM IDs
    const std::vector<std::shared_ptr<CRSScintillatorBar> > &counters = CRS->getAllCRSScintillatorBars();
    std::vector<std::shared_ptr<CRSScintillatorBar> >::const_iterator iter;
    int iSiPM = 0;
    std::map<int,int> sipm_map;
    for(iter=counters.begin(); iter!=counters.end(); iter++)
    {
      const CRSScintillatorBarIndex &barIndex = (*iter)->index();
      for(int SiPM=0; SiPM<4; SiPM++)
      {
        if(!(*iter)->getBarDetail().hasCMB(SiPM%2)) continue;
        sipm_map[barIndex.asInt()*4 + SiPM] = iSiPM;
        iSiPM++;
      }
    }

    // Loop through all reco pulses
    for(size_t recoPulseIndex=0; recoPulseIndex<crvRecoPulses->size(); recoPulseIndex++)
    {
      const art::Ptr<CrvRecoPulse> crvRecoPulse(crvRecoPulses, recoPulseIndex);
      //get information about the counter
      const CRSScintillatorBarIndex &barIndex = crvRecoPulse->GetScintillatorBarIndex();
      int sectorNumber  = -1;
      int moduleNumber  = -1;
      int layerNumber   = -1;
      int counterNumber = -1;
      CrvHelper::GetCrvCounterInfo(CRS, barIndex, sectorNumber, moduleNumber, layerNumber, counterNumber);

      //Reco pulses information
      int SiPM = crvRecoPulse->GetSiPMNumber();
      int SiPMId = sipm_map.find(barIndex.asInt()*4 + SiPM)->second;
      CLHEP::Hep3Vector HitPos = CrvHelper::GetCrvCounterPos(CRS, barIndex);
      recoInfo.emplace_back(HitPos, barIndex.asInt(), sectorNumber, SiPMId,
          crvRecoPulse->GetPEs(), crvRecoPulse->GetPEsPulseHeight(), crvRecoPulse->GetPulseHeight(),
          crvRecoPulse->GetPulseBeta(), crvRecoPulse->GetPulseFitChi2(), crvRecoPulse->GetPulseTime());

      //MCtruth pulses information
      double visibleEnergyDeposited  = 0;
      double earliestHitTime         = 0;
      CLHEP::Hep3Vector earliestHitPos;
      art::Ptr<SimParticle> mostLikelySimParticle;
      //for this reco pulse
      CrvMCHelper::GetInfoFromCrvRecoPulse(crvRecoPulse, crvDigiMCs, visibleEnergyDeposited,
          earliestHitTime, earliestHitPos, mostLikelySimParticle);

      bool hasMCInfo = (mostLikelySimParticle.isNonnull()?true:false); //MC
      if(hasMCInfo)
      {
        const art::Ptr<SimParticle> &primaryParticle = FindPrimaryParticle(mostLikelySimParticle);
        const art::Ptr<SimParticle> &parentParticle = FindParentParticle(mostLikelySimParticle);
        const art::Ptr<SimParticle> &gparentParticle = FindGParentParticle(mostLikelySimParticle);
        MCInfo.emplace_back(true, mostLikelySimParticle->pdgId(),
            primaryParticle->pdgId(), primaryParticle->startMomentum().e() - primaryParticle->startMomentum().m(), primaryParticle->startPosition(),
            parentParticle->pdgId(),  parentParticle->startMomentum().e()  - parentParticle->startMomentum().m(),  parentParticle->startPosition(),
            gparentParticle->pdgId(), gparentParticle->startMomentum().e() - gparentParticle->startMomentum().m(), gparentParticle->startPosition(),
            earliestHitPos, earliestHitTime, visibleEnergyDeposited);
      }
      else
        MCInfo.emplace_back();
    }

    //    Fill waveforms struct
    for(size_t j=0; j<crvDigis->size(); j++)
    {
      mu2e::CrvDigi const& digi(crvDigis->at(j));
      int _SiPMId = sipm_map.find(digi.GetScintillatorBarIndex().asInt()*4 + digi.GetSiPMNumber())->second;
      for(size_t k=0; k<mu2e::CrvDigi::NSamples; k++)
        waveformInfo.emplace_back(digi.GetADCs()[k], (digi.GetStartTDC()+k)*CRVDigitizationPeriod, _SiPMId);
    }
  } //FillCrvPulseInfoCollections

}
