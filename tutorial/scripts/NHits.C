void NHits() {

  std::string filelist = "filelists/nts.mu2e.CeEndpointMix1BBSignal.MDC2020z1_best_v1_1_std_v04_01_00.list";
  TString treename = "TrkAnaNeg/trkana";

  // Get the TChain ready
  TChain* trkana = new TChain(treename);

  std::ifstream input_filelist(filelist);
  if (input_filelist.is_open()) {
    std::string filename;
    while(std::getline(input_filelist,filename)) {
      trkana->Add(filename.c_str());
    }
    input_filelist.close();
  }

  TCanvas* c1 = new TCanvas("c1", "c1");
  c1->SetGridx();
  c1->SetGridy();

  TH1D* hist = new TH1D("h_nhits", "", 100,0,100);
  trkana->Draw("dem.nhits>>h_nhits", "", "goff");
  hist->GetXaxis()->SetTitle("Number of Hits");
  hist->GetYaxis()->SetTitle("Number of Tracks");
  hist->Draw();

  TH1D* hist2 = new TH1D("h_nactive", "", 100,0,100);
  trkana->Draw("dem.nactive>>h_nactive", "", "goff");
  hist2->SetLineColor(kRed);
  hist2->Draw("HIST SAME");

  TLegend* leg = new TLegend();
  leg->AddEntry(hist, "total number of hits", "l");
  leg->AddEntry(hist2, "total number of used hits", "l");
  leg->Draw();
}
