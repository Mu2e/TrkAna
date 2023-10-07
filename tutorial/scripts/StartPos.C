void StartPos() {

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

  double min_y = -100;
  double max_y = 100;
  double y_bin_width = 1;
  int n_y_bins=(max_y - min_y) / (y_bin_width);
  double min_x = -100;
  double max_x = +100;
  double x_bin_width = 1;
  int n_x_bins=(max_x - min_x) / (x_bin_width);

  TH2D* h_StartPos_XY = new TH2D("h_StartPos_XY", "", n_x_bins,min_x,max_x, n_y_bins,min_y,max_y);
  trkana->Draw("demmcsim.pos.y():demmcsim.pos.x()>>h_StartPos_XY", "demmcsim.prirel._rem==0");
  h_StartPos_XY->GetXaxis()->SetTitle("X Position (detector coords) [mm]");
  h_StartPos_XY->GetYaxis()->SetTitle("Y Position (detector coords) [mm]");
  h_StartPos_XY->Draw("COLZ");
}
