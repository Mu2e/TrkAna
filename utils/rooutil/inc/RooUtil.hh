#ifndef RooUtil_hh_
#define RooUtil_hh_

#include "TFile.h"
#include "TTree.h"

#include "TrkAna/utils/rooutil/inc/Event.hh"

class RooUtil {
public:
  RooUtil(std::string filename, std::string treename = "EventNtuple/ntuple") {
    TFile* file = new TFile(filename.c_str(), "READ");
    ntuple = (TTree*) file->Get(treename.c_str());
    event = new Event(ntuple);
  }

  int GetNEvents() { return ntuple->GetEntries(); }

  const Event& GetEvent(int i_event) {
    ntuple->GetEntry(i_event);
    return *event;
  }

private:
  TTree* ntuple;
  Event* event; // holds all the variables for SetBranchAddress
};

#endif
