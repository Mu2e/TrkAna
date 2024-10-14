//
// MVAResultInfo: array branch containing the output of a multi-variate analysis (MVA)
// structs used to record MVAResult information into EventNtuple
// Andy Edmonds (January 2024)
//
#ifndef MVAResultInfo_HH
#define MVAResultInfo_HH
namespace mu2e
{
// general info about the SimParticle which was simulated
  struct MVAResultInfo {
    bool valid = false; // whether this information is valid or not
    float result = -1.0; // the numerical result of the MVA
    void reset() { *this = MVAResultInfo(); }
  };
}
#endif
