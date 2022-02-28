//
//  Struct for HelixSeed info
//
#ifndef TrkAna_HelixInfo_hh
#define TrkAna_HelixInfo_hh
namespace mu2e {
  struct HelixInfo {
    int nch, ncha;
    int nsh, nsha;
    unsigned flag;
    float t0err;
    float mom;
    float chi2xy;
    float chi2fz;
    float ecalo;
    void reset() { nch = nsh = ncha = nsha = -1; flag = 0;
      t0err = mom = chi2xy = chi2fz = ecalo =-1.0; }
  };
}
#endif
