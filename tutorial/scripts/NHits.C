void NHits() {

  TString filename = "nts.brownd.CeEndpointMix1BBSignal.MDC2020z_TKAv04.tka";
  TString treename = "TrkAnaNeg/trkana";

  // Open the TrkAna ROOT file for reading
  TFile* file = new TFile(filename, "READ");

  // Get the TrkAna tree from the file
  TTree* trkana = (TTree*) file->Get(treename);

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
