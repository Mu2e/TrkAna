void RecoMom() {

  TString filename = "nts.brownd.CeEndpointMix1BBSignal.MDC2020z_TKAv04.tka";
  TString treename = "TrkAnaNeg/trkana";

  // Open the TrkAna ROOT file for reading
  TFile* file = new TFile(filename, "READ");

  // Get the TrkAna tree from the file
  TTree* trkana = (TTree*) file->Get(treename);

  TCanvas* c1 = new TCanvas("c1", "c1");
  c1->SetGridx();
  c1->SetGridy();

  double min_mom = 100;
  double max_mom = 107;
  double mom_bin_width = 0.1;
  int n_mom_bins = (max_mom - min_mom) / mom_bin_width;

  TH1D* h_EntMom = new TH1D("h_EntMom", "", n_mom_bins,min_mom,max_mom);
  trkana->Draw("demfit.mom.R()>>h_EntMom", "demfit.sid==0", "goff");
  h_EntMom->GetXaxis()->SetTitle("Reconstructed Momentum at Tracker Entrance[MeV/c]");
  h_EntMom->GetYaxis()->SetTitle("Number of Tracks");
  h_EntMom->Draw();


  TH1D* h_EntMom_timecut = new TH1D("h_EntMom_timecut", "", n_mom_bins,min_mom,max_mom);
  trkana->Draw("demfit.mom.R()>>h_EntMom_timecut", "demfit.sid==0 && demlh.t0>=700", "goff");
  h_EntMom_timecut->SetLineColor(kRed);
  h_EntMom_timecut->Draw("HIST SAME");


  TLegend* leg = new TLegend();
  leg->AddEntry(h_EntMom, "all tracks", "l");
  leg->AddEntry(h_EntMom_timecut, "t0 >= 700 ns", "l");
  leg->Draw();
}
