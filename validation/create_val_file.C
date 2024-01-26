void create_val_file() {

  TFile* trkana_file = new TFile("/pnfs/mu2e/tape/phy-nts/nts/mu2e/CeEndpointMix1BBSignal/MDC2020z1_best_v1_1_std_v04_01_00/tka/85/7b/nts.mu2e.CeEndpointMix1BBSignal.MDC2020z1_best_v1_1_std_v04_01_00.001210_00000289.tka", "READ");
  TTree* trkana = (TTree*) trkana_file->Get("TrkAnaNeg/trkana");

  TFile* file = new TFile("val-trkana.root", "RECREATE");

  // evtinfo Histograms
  trkana->Draw("evtinfo.eventid>>h_evtinfo_eventid", "", "");
  trkana->Draw("evtinfo.subrunid>>h_evtinfo_subrunid", "", "");
  trkana->Draw("evtinfo.runid>>h_evtinfo_runid", "", "");
  trkana->Draw("evtinfo.nprotons>>h_evtinfo_nprotons", "", "");
  trkana->Draw("evtinfo.pbtime>>h_evtinfo_pbtime", "", "");
  trkana->Draw("evtinfo.pbterr>>h_evtinfo_pbterr", "", "");

  // evtinfomc Histograms
  trkana->Draw("evtinfomc.nprotons>>h_evtinfomc_nprotons", "", "");
  trkana->Draw("evtinfomc.pbtime>>h_evtinfomc_pbtime", "", "");

  // demfit Histograms
  trkana->Draw("demfit.mom.R()>>h_demfit_mom_all", "", "goff");
  trkana->Draw("demfit.mom.R()>>h_demfit_mom_ent", "demfit.sid==0", "goff");
  trkana->Draw("demfit.mom.R()>>h_demfit_mom_mid", "demfit.sid==1", "goff");
  trkana->Draw("demfit.mom.R()>>h_demfit_mom_xit", "demfit.sid==2", "goff");
  trkana->Draw("demfit.mom.R()>>h_demfit_mom_ent_t0cut", "demfit.sid==0 && demlh.t0>=700", "goff");
  trkana->Draw("demfit.mom.R()>>h_demfit_mom_mid_t0cut", "demfit.sid==1 && demlh.t0>=700", "goff");
  trkana->Draw("demfit.mom.R()>>h_demfit_mom_xit_t0cut", "demfit.sid==2 && demlh.t0>=700", "goff");

  file->Write();
  file->Close();
}
