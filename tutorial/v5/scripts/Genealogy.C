void Genealogy() {

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

  double min_z = -20000;
  double max_z = 1000;
  double z_bin_width = 100;
  int n_z_bins=(max_z - min_z) / (z_bin_width);
  double min_x = -700;
  double max_x = +9000;
  double x_bin_width = 100;
  int n_x_bins=(max_x - min_x) / (x_bin_width);

  TH2D* h_StartPos_XZ = new TH2D("h_StartPos_XZ", "", n_z_bins,min_z,max_z, n_x_bins,min_x,max_x);
  trkana->Draw("demmcsim.pos.x():demmcsim.pos.z()>>h_StartPos_XZ", "demmcsim.prirel._rem==1 && demmcsim.prirel._rel==2");
  h_StartPos_XZ->GetXaxis()->SetTitle("Z Position (detector coords) [mm]");
  h_StartPos_XZ->GetYaxis()->SetTitle("X Position (detector coords) [mm]");
  h_StartPos_XZ->Draw("COLZ");


  TCanvas* c2 = new TCanvas("c2", "c2");
  c2->SetGridx();
  c2->SetGridy();


  TH2D* h_StartPos_DIO = new TH2D("h_StartPos_DIO", "", 100, -5500, 1000, 100,0,500);
  //  trkana->Draw("demmcsim.pos.rho():demmcsim.pos.z()>>h_StartPos_DIO", "demmcsim.gen==114 && demmcsim.trkrel._rem==0");
  trkana->Draw("demmcsim.pos.rho():demmcsim.pos.z()>>h_StartPos_DIO", "demmcsim.gen==166 && demmcsim.trkrel._rem==0");
  h_StartPos_DIO->SetXTitle("Momentum at Creation [MeV/c]");
  h_StartPos_DIO->Draw("COLZ");
}
