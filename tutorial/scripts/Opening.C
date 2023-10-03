void Opening(TString filename) {

  TString treename = "TrkAnaNeg/trkana";

  // Open the TrkAna ROOT file for reading
  TFile* file = new TFile(filename, "READ");

  // Get the TrkAna tree from the file. (Note that the (TTree*) is needed to "cast" the object to the correct class)
  TTree* trkana = (TTree*) file->Get(treename);

  trkana->Print();
  trkana->Scan("evtinfo.runid:evtinfo.subrunid:evtinfo.eventid:demfit[0].mom.R()");
}
