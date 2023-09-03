// This script produces the same plot as ROOTCommandLine.C, but adds axis labels and a legend

void ROOTScript() {

  // Open file and get trkana tree
  std::string filename = "nts.owner.trkana-reco.version.sequencer.root";
  std::string treename = "TrkAnaNeg/trkana";
  TFile* file = new TFile(filename.c_str(), "READ");
  TTree* trkana = (TTree*) file->Get(treename.c_str());

  // Define and create histograms
  double min_mom = 90;
  double max_mom = 110;
  double mom_width = 0.2;
  int n_mom_bins = (max_mom - min_mom) / mom_width;
  TH1F* hMom = new TH1F("hMom", "Reconstructed Momentum", n_mom_bins,min_mom,max_mom);
  TH1F* hMom_t0Cut = new TH1F("hMom_t0Cut", "Reconstructed Momentum", n_mom_bins,min_mom, max_mom);

  // Fill histograms
  trkana->Draw("demfit[0].mom.R()>>hMom", "", "goff"); // "goff" means don't draw yet
  trkana->Draw("demfit[0].mom.R()>>hMom_t0Cut", "demlh[0].t0>700", "goff");

  // Set line color and axis labels of histograms
  hMom->SetLineColor(kRed);
  hMom->SetXTitle("Reco Mom [MeV/c]");
  std::stringstream axistitle;
  axistitle.str("");
  axistitle << "Count / " << hMom->GetBinWidth(1) << " MeV/c";
  hMom->SetYTitle(axistitle.str().c_str());

  // Draw histograms
  hMom->Draw("HIST");
  hMom_t0Cut->Draw("HIST SAME");

  // Create, fill and draw TLegend
  TLegend* leg = new TLegend(0.2, 0.5, 0.5, 0.8); // defined in NDC coordinates (i.e. fraction of canvas)
  leg->SetBorderSize(0);
  leg->SetTextSize(0.035);
  leg->SetFillColor(kWhite);
  leg->AddEntry(hMom, "All Tracks");
  leg->AddEntry(hMom_t0Cut, "demlh[0].t0 > 700 ns");
  leg->Draw();
}
