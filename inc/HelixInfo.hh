//
//  Struct for HelixSeed info
//
#ifndef TrkAna_HelixInfo_hh
#define TrkAna_HelixInfo_hh
namespace mu2e {
  struct HelixInfo {
    int nch = -1;
    int ncha = -1;
    int nsh = -1;
    int nsha = -1;
    int flag = -1;
    float t0err = -1;
    float mom = -1;
    float chi2xy = -1;
    float chi2fz = -1;
    float ecalo = -1;
    void reset() { *this = HelixInfo(); }
  };
}
#endif
