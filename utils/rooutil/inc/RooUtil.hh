#ifndef RooUtil_hh_
#define RooUtil_hh_

#include "TFile.h"
#include "TTree.h"

#include "EventNtuple/utils/rooutil/inc/Event.hh"

class RooUtil {
public:
  RooUtil(std::string filename, std::string treename = "EventNtuple/ntuple", bool debug = false) : debug(debug) {
    if (debug) {
      std::cout << "RooUtil::RooUtil(): Opening file " << filename << "..." << std::endl;
    }
    TFile* file = new TFile(filename.c_str(), "READ");

    if (debug) {
      std::cout << "RooUtil::RooUtil(): Extracting ntuple " << treename << "..." << std::endl;
    }
    ntuple = (TTree*) file->Get(treename.c_str());

    if (debug) {
      std::cout << "RooUtil::RooUtil(): Creating event..." << std::endl;
    }
    event = new Event(ntuple, debug);

    if (debug) {
      std::cout << "RooUtil::RooUtil(): All done." << std::endl;
    }
  }

  void SetDebug(bool dbg) { debug = dbg; }
  int GetNEvents() { return ntuple->GetEntries(); }

  const Event& GetEvent(int i_event) {
    if (debug) {
      std::cout << "RooUtil::GetEvent(): Getting event #" << i_event << "..." << std::endl;
    }
    ntuple->GetEntry(i_event);

    if (debug) {
      std::cout << "RooUtil::GetEvent(): Updating Event..." << std::endl;
    }
    event->Update();

    if (debug) {
      std::cout << "RooUtil::GetEvent(): All done." << std::endl;
    }
    return *event;
  }

private:
  TTree* ntuple;
  Event* event; // holds all the variables for SetBranchAddress
  bool debug;
};

#endif
