void create_val_file() {

  TFile* trkana_file = new TFile("/pnfs/mu2e/tape/phy-nts/nts/mu2e/CeEndpointMix1BBSignal/MDC2020z1_best_v1_1_std_v04_01_00/tka/85/7b/nts.mu2e.CeEndpointMix1BBSignal.MDC2020z1_best_v1_1_std_v04_01_00.001210_00000289.tka", "READ");
  TTree* trkana = (TTree*) trkana_file->Get("TrkAnaNeg/trkana");

  TFile* file = new TFile("val-trkana.root", "RECREATE");

  // Histograms to create
  double min_mom = 0;
  double max_mom = 1000;
  int n_mom_bins = 1000;
  TH1D* h_reco_mom_all = new TH1D("h_reco_mom_all", "h_reco_mom_all", n_mom_bins,min_mom,max_mom);

  trkana->Draw("demfit.mom.R()>>h_reco_mom_all", "", "goff");

  h_reco_mom_all->Write();

  file->Close();

}
