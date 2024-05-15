//
// struct to place variables that are used for TrkQual calculation
//
#ifndef TrkQualInfo_HH
#define TrkQualInfo_HH
#include "Offline/RecoDataProducts/inc/TrkQual.hh"
#include "Rtypes.h"
namespace mu2e
{
// general information about a track
  struct TrkQualInfo {
    Float_t trkqualvars[TrkQualDetail::n_vars];
    Float_t mvaout;
    Int_t mvastat;

    TrkQualInfo() { reset(); }

    void reset() {
      int n_trkqual_vars = TrkQual::n_vars;
      for (int i_trkqual_var = 0; i_trkqual_var < n_trkqual_vars; ++i_trkqual_var) {
        trkqualvars[i_trkqual_var] = -1000.0;
      }
      mvaout = -1000.0;
      mvastat = -1;
    }

    static std::string const leafnames() {
      std::string leaves = "";
      int n_trkqual_vars = TrkQual::n_vars;
      for (int i_trkqual_var = 0; i_trkqual_var < n_trkqual_vars; ++i_trkqual_var) {
        TrkQual::MVA_varindex i_index =TrkQual::MVA_varindex(i_trkqual_var);
        std::string varname = TrkQual::varName(i_index);
        leaves += varname + "/F:";
      }
      leaves += "mvaout/F:mvastat/I";
      return leaves;
    }
  };
}
#endif
