void create_val_file() {

  TFile* trkana_file = new TFile("/pnfs/mu2e/tape/phy-nts/nts/mu2e/CeEndpointMix1BBSignal/MDC2020z1_best_v1_1_std_v04_01_00/tka/85/7b/nts.mu2e.CeEndpointMix1BBSignal.MDC2020z1_best_v1_1_std_v04_01_00.001210_00000289.tka", "READ");
  TTree* trkana = (TTree*) trkana_file->Get("TrkAnaNeg/trkana");

  TFile* file = new TFile("val-trkana.root", "RECREATE");

  // evtinfo histograms
  trkana->Draw("evtinfo.eventid>>h_evtinfo_eventid", "", "");
  trkana->Draw("evtinfo.subrunid>>h_evtinfo_subrunid", "", "");
  trkana->Draw("evtinfo.runid>>h_evtinfo_runid", "", "");
  trkana->Draw("evtinfo.nprotons>>h_evtinfo_nprotons", "", "");
  trkana->Draw("evtinfo.pbtime>>h_evtinfo_pbtime", "", "");
  trkana->Draw("evtinfo.pbterr>>h_evtinfo_pbterr", "", "");

  // evtinfomc histograms
  trkana->Draw("evtinfomc.nprotons>>h_evtinfomc_nprotons", "", "");
  trkana->Draw("evtinfomc.pbtime>>h_evtinfomc_pbtime", "", "");

  // demfit histograms
  trkana->Draw("demfit.mom.R()>>h_demfit_mom_all", "", "goff");
  trkana->Draw("demfit.mom.R()>>h_demfit_mom_ent", "demfit.sid==0", "goff");
  trkana->Draw("demfit.mom.R()>>h_demfit_mom_mid", "demfit.sid==1", "goff");
  trkana->Draw("demfit.mom.R()>>h_demfit_mom_xit", "demfit.sid==2", "goff");
  trkana->Draw("demfit.mom.R()>>h_demfit_mom_ent_t0cut", "demfit.sid==0 && demlh.t0>=700", "goff");
  trkana->Draw("demfit.mom.R()>>h_demfit_mom_mid_t0cut", "demfit.sid==1 && demlh.t0>=700", "goff");
  trkana->Draw("demfit.mom.R()>>h_demfit_mom_xit_t0cut", "demfit.sid==2 && demlh.t0>=700", "goff");

  // resolution histograms
  trkana->Draw("(demfit[demmcvd.iinter].mom.R() - demmcvd.mom.R())>>h_demfit_momres_all", "", "goff");
  trkana->Draw("(demfit[demmcvd.iinter].mom.R() - demmcvd.mom.R())>>h_demfit_momres_ent", "demmcvd.sid==0", "goff");
  trkana->Draw("(demfit[demmcvd.iinter].mom.R() - demmcvd.mom.R())>>h_demfit_momres_mid", "demmcvd.sid==1", "goff");
  trkana->Draw("(demfit[demmcvd.iinter].mom.R() - demmcvd.mom.R())>>h_demfit_momres_xit", "demmcvd.sid==2", "goff");

  // trkcalohit histograms
  trkana->Draw("demtch.ctime>>h_demtch_ctime_all", "", "goff");
  trkana->Draw("demtch.ctime>>h_demtch_ctime_active", "demtch.active==1", "goff");
  trkana->Draw("demtch.ctime>>h_demtch_ctime_inactive", "demtch.active==0", "goff");
  trkana->Draw("demtch.ctime-demlh.t0>>h_demtch_demfit_dt_ent", "demfit.sid==0 && demtch.active==1", "goff");

  // crv histograms
  trkana->Draw("crvsummary.totalPEs>>h_crvsummary_totalPEs_all", "", "goff");
  trkana->Draw("crvhit.pos.fCoordinates.fX>>h_crvhit_pos_x", "", "goff");
  trkana->Draw("crvhit.pos.fCoordinates.fY>>h_crvhit_pos_y", "", "goff");
  trkana->Draw("crvhit.pos.fCoordinates.fZ>>h_crvhit_pos_z", "", "goff");
  trkana->Draw("crvhitmc.primary.fCoordinates.fX>>h_crvhitmc_primary_x", "", "goff");
  trkana->Draw("crvhitmc.primary.fCoordinates.fY>>h_crvhitmc_primary_y", "", "goff");
  trkana->Draw("crvhitmc.primary.fCoordinates.fZ>>h_crvhitmc_primary_z", "", "goff");
  trkana->Draw("crvhitmc.depositedEnergy>>h_crvhitmc_depostedEnergy", "", "goff");

  // demmcsim histograms
  trkana->Draw("demmcsim.pos.x()>>h_demmcsim_pos_x_all", "", "goff");
  trkana->Draw("demmcsim.pos.y()>>h_demmcsim_pos_y_all", "", "goff");
  trkana->Draw("demmcsim.pos.z()>>h_demmcsim_pos_z_all", "", "goff");
  trkana->Draw("demmcsim.pos.x()>>h_demmcsim_pos_x_evtprimary", "demmcsim.prirel._rel==0 && demmcsim.prirel._rem==0", "goff");
  trkana->Draw("demmcsim.pos.y()>>h_demmcsim_pos_y_evtprimary", "demmcsim.prirel._rel==0 && demmcsim.prirel._rem==0", "goff");
  trkana->Draw("demmcsim.pos.z()>>h_demmcsim_pos_z_evtprimary", "demmcsim.prirel._rel==0 && demmcsim.prirel._rem==0", "goff");
  trkana->Draw("demmcsim.pos.x()>>h_demmcsim_pos_x_trkprimary", "demmcsim.trkrel._rel==0 && demmcsim.trkrel._rem==0", "goff");
  trkana->Draw("demmcsim.pos.y()>>h_demmcsim_pos_y_trkprimary", "demmcsim.trkrel._rel==0 && demmcsim.trkrel._rem==0", "goff");
  trkana->Draw("demmcsim.pos.z()>>h_demmcsim_pos_z_trkprimary", "demmcsim.trkrel._rel==0 && demmcsim.trkrel._rem==0", "goff");
  trkana->Draw("demmcsim.pos.x()>>h_demmcsim_pos_x_trkparent", "demmcsim.trkrel._rel==2 && demmcsim.trkrel._rem==1", "goff");
  trkana->Draw("demmcsim.pos.y()>>h_demmcsim_pos_y_trkparent", "demmcsim.trkrel._rel==2 && demmcsim.trkrel._rem==1", "goff");
  trkana->Draw("demmcsim.pos.z()>>h_demmcsim_pos_z_trkparent", "demmcsim.trkrel._rel==2 && demmcsim.trkrel._rem==1", "goff");
  trkana->Draw("demmcsim.pos.x()>>h_demmcsim_pos_x_trkgparent", "demmcsim.trkrel._rel==5 && demmcsim.trkrel._rem==2", "goff");
  trkana->Draw("demmcsim.pos.y()>>h_demmcsim_pos_y_trkgparent", "demmcsim.trkrel._rel==5 && demmcsim.trkrel._rem==2", "goff");
  trkana->Draw("demmcsim.pos.z()>>h_demmcsim_pos_z_trkgparent", "demmcsim.trkrel._rel==5 && demmcsim.trkrel._rem==2", "goff");
  trkana->Draw("demmcsim.pos.x()>>h_demmcsim_pos_x_trkggparent", "demmcsim.trkrel._rel==5 && demmcsim.trkrel._rem==3", "goff");
  trkana->Draw("demmcsim.pos.y()>>h_demmcsim_pos_y_trkggparent", "demmcsim.trkrel._rel==5 && demmcsim.trkrel._rem==3", "goff");
  trkana->Draw("demmcsim.pos.z()>>h_demmcsim_pos_z_trkggparent", "demmcsim.trkrel._rel==5 && demmcsim.trkrel._rem==3", "goff");


  file->Write();
  file->Close();
}
