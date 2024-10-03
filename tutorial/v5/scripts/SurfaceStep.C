void SurfaceStep() {

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
  c1->SetLogy();

  TH2D* h_EDep = new TH2D("h_EDep", "Target Foil Energy Loss vs Polar Angle;#Theta (radians);Energy Loss (MeV)", 50,0.5,2.5,50 0,5,0);
  trkana->Draw("trkmcssi.edep:trkmcssi.mom.Theta()>>h_EDep","trkmcssi.sid==104");

  TLegend* leg = new TLegend();
  leg->AddEntry(h_MomRes, "all tracks", "l");
  leg->Draw();
}
