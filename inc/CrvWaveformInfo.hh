#ifndef CrvWaveformInfo_hh
#define CrvWaveformInfo_hh

#include <vector>
#include "Rtypes.h"

namespace mu2e
{
  struct CrvWaveformInfo   //information about CRV waveforms
  {
    Float_t adc = -1;
    Float_t time = -1;
    Int_t   SiPMId = -1;
    CrvWaveformInfo(){}
    CrvWaveformInfo(float adc, float time, int SiPMId) :
      adc(adc),
      time(time),
      SiPMId(SiPMId)
    {}
  };

  typedef std::vector<CrvWaveformInfo> CrvWaveformInfoCollection;  //this is the reco vector which will be stored in the main TTree

}
#endif
