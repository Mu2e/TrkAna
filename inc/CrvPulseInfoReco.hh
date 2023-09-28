#ifndef CrvPulseInfoReco_hh
#define CrvPulseInfoReco_hh

#include "CLHEP/Vector/ThreeVector.h"
#include <vector>
#include <map>
#include "Rtypes.h"

namespace mu2e
{

  struct CrvPulseInfoReco   //information about CRV reco pulses
  {

    XYZVectorF pos;           //average position of counters
    Int_t    barId = -1;           //CRV counter ID
    Int_t    sectorId = -1;        //CRV sector ID
    Int_t    SiPMId = -1;          //SiPMId number
    Int_t    PEs = -1;             //PEs using pulse integral
    Int_t    PEsPulseHeight = -1;  //PEs using pulse height
    Float_t  pulseHeight = -1;     //Pulse height
    Float_t  pulseBeta = -1;       //Pulse beta
    Float_t  pulseFitChi2 = -1;    //Pulse Fit chi2
    Float_t  time = -1;            //Time

    CrvPulseInfoReco(){}
    CrvPulseInfoReco(CLHEP::Hep3Vector ppos, int barId, int sectorId, int SiPMId, int PEs, int PEsPulseHeight, float pulseHeight, float pulseBeta, float pulseFitChi2, float time) :
      pos(ppos),
      barId(barId),
      sectorId(sectorId),
      SiPMId(SiPMId),
      PEs(PEs),
      PEsPulseHeight(PEsPulseHeight),
      pulseHeight(pulseHeight),
      pulseBeta(pulseBeta),
      pulseFitChi2(pulseFitChi2),
      time(time)
    {}
  };

  typedef std::vector<CrvPulseInfoReco> CrvPulseInfoRecoCollection;  //this is the reco vector which will be stored in the main TTree

}
#endif
