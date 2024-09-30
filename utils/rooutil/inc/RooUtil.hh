#ifndef RooUtil_hh_
#define RooUtil_hh_

#include "TFile.h"
#include "TTree.h"

class RooUtil {
public:
  RooUtil(std::string filename, std::string treename = "EventNtuple/ntuple") {
    TFile* file = new TFile(filename.c_str(), "READ");
    ntuple = (TTree*) file->Get(treename.c_str());
  }

  int GetNEvents() { return ntuple->GetEntries(); }

private:
  TTree* ntuple;

};

#endif
