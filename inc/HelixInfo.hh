//
// HelixInfo: struct for HelixSeed info
//
#ifndef TrkAna_HelixInfo_hh
#define TrkAna_HelixInfo_hh
namespace mu2e {
  struct HelixInfo {
    int nch = -1; // number of combo hits potentially used for this helix
    int ncha = -1; // number of combo hits that are not "outliers"
    int nsh = -1; // number of straw hits in the combo hits potentially used for this helix
    int nsha = -1; // number of straw hits in the combo hits that are not "outliers"
    int flag = -1; // flag for algorithm used (TPR = 0, CPR = 1, APR = 2, MPR = 3)
    float t0err = -1; // uncertainty on time
    float mom = -1; // momentum
    float chi2xy = -1; // squared sum of the hit residuals wrt the XY plane normalized by the degree of freedom
    float chi2fz = -1; // squared sum of the hit residuals wrt the ZPhi plane normalized by the degree of freedom
    float ecalo = -1; // energy deposited in calo cluster
    void reset() { *this = HelixInfo(); }
  };
}
#endif
