void NHits() {

  std::string filelist = "filelists/nts.mu2e.CeEndpointMix1BBSignal.MDC2020z1_best_v1_1_std_v05_00_00rc.list";
  TString treename = "TrkAna/trkana";

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
  hist->SetTitle("All Events");
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

  TCanvas* c2 = new TCanvas("c2", "c2");
  c2->SetGridx();
  c2->SetGridy();

  TH1D* hist3 = new TH1D("h_nhits_ndem2", "", 100,0,100);
  trkana->Draw("dem.nhits>>h_nhits_ndem2", "tcnt.ndem==2", "goff");
  hist3->SetTitle("Events with 2 dem tracks");
  hist3->GetXaxis()->SetTitle("Number of Hits");
  hist3->GetYaxis()->SetTitle("Number of Tracks");
  hist3->Draw();

  TH1D* hist4 = new TH1D("h_nactive_ndem2", "", 100,0,100);
  trkana->Draw("dem.nactive>>h_nactive_ndem2", "tcnt.ndem==2", "goff");
  hist4->SetLineColor(kRed);
  hist4->Draw("HIST SAME");

  TLegend* leg2 = new TLegend();
  leg2->AddEntry(hist3, "total number of hits", "l");
  leg2->AddEntry(hist4, "total number of used hits", "l");
  leg2->Draw();
}
