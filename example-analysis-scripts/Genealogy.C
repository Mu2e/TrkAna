void Genealogy() {

  // Open file and get trkana tree
  std::string filename = "nts.owner.trkana-reco.version.sequencer.root";
  std::string treename = "TrkAnaNeg/trkana";
  TFile* file = new TFile(filename.c_str(), "READ");
  TTree* trkana = (TTree*) file->Get(treename.c_str());

  // Draw histograms
  TCanvas* c1 = new TCanvas("c1", "c1");
  c1->Divide(2,3);

  c1->cd(1);
  trkana->Draw("demmcsim.mom.R()>>hMomGen0(100,100,110)", "demmcsim.generation==0", "PLC"); // "PLC" means new colors will be picked automatically
  trkana->Draw("demmcsim.mom.R()>>hMomGen0_Ce(100,100,110)", "demmcsim.generation==0 && demmcsim.gen==167", "PFC SAME");
  TH1D* hMomGen0 = ((TH1D*)c1->GetPad(1)->GetPrimitive("hMomGen0"));
  hMomGen0->SetTitle("");
  TH1D* hMomGen0_Ce = ((TH1D*)c1->GetPad(1)->GetPrimitive("hMomGen0_Ce"));
  TLegend* leg_1 = new TLegend(0.2, 0.5, 0.4, 0.8); // defined in NDC coordinates (i.e. fraction of canvas)
  leg_1->SetBorderSize(0);
  leg_1->SetTextSize(0.035);
  leg_1->SetFillColor(kWhite);
  leg_1->AddEntry(hMomGen0, "generation = -1", "l");
  leg_1->AddEntry(hMomGen0_Ce, "generation = -1 and proc=CeEndpoint", "f");
  leg_1->Draw();

  c1->cd(2);
  trkana->Draw("demmcsim.mom.R()>>hMomGen_min1(100,0,100)", "demmcsim.generation==-1", "PLC"); // "PLC" means new colors will be picked automatically
  trkana->Draw("demmcsim.mom.R()>>hMomGen_min1_mu(100,0,100)", "demmcsim.generation==-1 && demmcsim.pdg==13", "PFC SAME");
  TH1D* hMomGen_min1 = ((TH1D*)c1->GetPad(2)->GetPrimitive("hMomGen_min1"));
  hMomGen_min1->SetTitle("");
  TH1D* hMomGen_min1_mu = ((TH1D*)c1->GetPad(2)->GetPrimitive("hMomGen_min1_mu"));
  TLegend* leg_2 = new TLegend(0.2, 0.5, 0.4, 0.8); // defined in NDC coordinates (i.e. fraction of canvas)
  leg_2->SetBorderSize(0);
  leg_2->SetTextSize(0.035);
  leg_2->SetFillColor(kWhite);
  leg_2->AddEntry(hMomGen_min1, "generation = -1", "l");
  leg_2->AddEntry(hMomGen_min1_mu, "generation = -1 and pdg=mu-", "f");
  leg_2->Draw();

  c1->cd(3);
  trkana->Draw("demmcsim.mom.R()>>hMomGen_min2(100,0,200)", "demmcsim.generation==-2", "PLC"); // "PLC" means new colors will be picked automatically
  trkana->Draw("demmcsim.mom.R()>>hMomGen_min2_pi(100,0,200)", "demmcsim.generation==-2 && demmcsim.pdg==-211", "PFC SAME");
  TH1D* hMomGen_min2 = ((TH1D*)c1->GetPad(3)->GetPrimitive("hMomGen_min2"));
  hMomGen_min2->SetTitle("");
  TH1D* hMomGen_min2_pi = ((TH1D*)c1->GetPad(3)->GetPrimitive("hMomGen_min2_pi"));
  TLegend* leg_3 = new TLegend(0.2, 0.5, 0.4, 0.8); // defined in NDC coordinates (i.e. fraction of canvas)
  leg_3->SetBorderSize(0);
  leg_3->SetTextSize(0.035);
  leg_3->SetFillColor(kWhite);
  leg_3->AddEntry(hMomGen_min2, "generation = -2", "l");
  leg_3->AddEntry(hMomGen_min2_pi, "generation = -2 and pdg=pi-", "f");
  leg_3->Draw();


  c1->cd(4);
  trkana->Draw("demmcsim.mom.R()>>hMomGen_min3(100,0,9000)", "demmcsim.generation==-3", "PLC"); // "PLC" means new colors will be picked automatically
  trkana->Draw("demmcsim.mom.R()>>hMomGen_min3_pot(100,0,9000)", "demmcsim.generation==-3 && demmcsim.gen==56", "PFC SAME");
  TH1D* hMomGen_min3 = ((TH1D*)c1->GetPad(4)->GetPrimitive("hMomGen_min3"));
  hMomGen_min3->SetTitle("");
  TH1D* hMomGen_min3_pot = ((TH1D*)c1->GetPad(4)->GetPrimitive("hMomGen_min3_pot"));
  TLegend* leg_4 = new TLegend(0.2, 0.5, 0.4, 0.8); // defined in NDC coordinates (i.e. fraction of canvas)
  leg_4->SetBorderSize(0);
  leg_4->SetTextSize(0.035);
  leg_4->SetFillColor(kWhite);
  leg_4->AddEntry(hMomGen_min3, "generation = -3", "l");
  leg_4->AddEntry(hMomGen_min3_pot, "generation = -3 and proc=POT", "f");
  leg_4->Draw();

  c1->cd(5);
  trkana->Draw("demmcsim.mom.R()>>hMomGen_min4(100,0,9000)", "demmcsim.generation==-4", "PLC"); // "PLC" means new colors will be picked automatically
  trkana->Draw("demmcsim.mom.R()>>hMomGen_min4_pot(100,0,9000)", "demmcsim.generation==-4 && demmcsim.gen==56", "PFC SAME");
  TH1D* hMomGen_min4 = ((TH1D*)c1->GetPad(5)->GetPrimitive("hMomGen_min4"));
  hMomGen_min4->SetTitle("");
  TH1D* hMomGen_min4_pot = ((TH1D*)c1->GetPad(5)->GetPrimitive("hMomGen_min4_pot"));
  TLegend* leg_5 = new TLegend(0.2, 0.5, 0.4, 0.8); // defined in NDC coordinates (i.e. fraction of canvas)
  leg_5->SetBorderSize(0);
  leg_5->SetTextSize(0.035);
  leg_5->SetFillColor(kWhite);
  leg_5->AddEntry(hMomGen_min4, "generation = -4", "l");
  leg_5->AddEntry(hMomGen_min4_pot, "generation = -4 and proc=POT", "f");
  leg_5->Draw();

  c1->cd(6);
  trkana->Draw("demmcsim.mom.R()>>hMomGen_pot(100,0,9000)", "demmcsim.gen==56", "PLC");
  TH1D* hMomGen_pot = ((TH1D*)c1->GetPad(6)->GetPrimitive("hMomGen_pot"));
  hMomGen_pot->SetTitle("");
  TLegend* leg_6 = new TLegend(0.2, 0.5, 0.4, 0.8); // defined in NDC coordinates (i.e. fraction of canvas)
  leg_6->SetBorderSize(0);
  leg_6->SetTextSize(0.035);
  leg_6->SetFillColor(kWhite);
  leg_6->AddEntry(hMomGen_pot, "all generations and proc=POT", "l");
  leg_6->Draw();
}
