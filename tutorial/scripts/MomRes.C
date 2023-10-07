void MomRes() {

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
  c1->SetLogy();

  double min_mom_res = -4;
  double max_mom_res = 4;
  double mom_res_bin_width = 0.05;
  int n_mom_res_bins = (max_mom_res - min_mom_res) / mom_res_bin_width;

  TH1D* h_MomRes = new TH1D("h_MomRes", "", n_mom_res_bins,min_mom_res,max_mom_res);
  trkana->Draw("(demfit[demmcvd.iinter].mom.R() - demmcvd.mom.R())>>h_MomRes", "demmcvd.sid==0", "goff");
  h_MomRes->GetXaxis()->SetTitle("Momentum Resolution at Tracker Entrance [MeV/c]");
  h_MomRes->GetYaxis()->SetTitle("Number of Tracks");
  h_MomRes->Draw();


  TLegend* leg = new TLegend();
  leg->AddEntry(h_MomRes, "all tracks", "l");
  leg->Draw();
}
