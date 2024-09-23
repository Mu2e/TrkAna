void create_val_file(std::string filename, std::string outfilename) {

  TFile* ntuple_file = new TFile(filename.c_str(), "READ");
  TTree* ntuple = (TTree*) ntuple_file->Get("TrkAna/ntuple");

  TFile* file = new TFile(outfilename.c_str(), "RECREATE");

  // evtinfo histograms
  ntuple->Draw("evtinfo.event>>h_evtinfo_event", "", "");
  ntuple->Draw("evtinfo.subrun>>h_evtinfo_subrun", "", "");
  ntuple->Draw("evtinfo.run>>h_evtinfo_run", "", "");
  ntuple->Draw("evtinfo.nprotons>>h_evtinfo_nprotons", "", "");
  ntuple->Draw("evtinfo.pbtime>>h_evtinfo_pbtime", "", "");
  ntuple->Draw("evtinfo.pbterr>>h_evtinfo_pbterr", "", "");

  // evtinfomc histograms
  ntuple->Draw("evtinfomc.nprotons>>h_evtinfomc_nprotons", "", "");
  ntuple->Draw("evtinfomc.pbtime>>h_evtinfomc_pbtime", "", "");

  // demfit histograms
  ntuple->Draw("demfit.mom.R()>>h_demfit_mom_all", "", "goff");
  ntuple->Draw("demfit.mom.R()>>h_demfit_mom_ent", "demfit.sid==0", "goff");
  ntuple->Draw("demfit.mom.R()>>h_demfit_mom_mid", "demfit.sid==1", "goff");
  ntuple->Draw("demfit.mom.R()>>h_demfit_mom_xit", "demfit.sid==2", "goff");
  ntuple->Draw("demfit.mom.R()>>h_demfit_mom_ent_t0cut", "demfit.sid==0 && demlh.t0>=700", "goff");
  ntuple->Draw("demfit.mom.R()>>h_demfit_mom_mid_t0cut", "demfit.sid==1 && demlh.t0>=700", "goff");
  ntuple->Draw("demfit.mom.R()>>h_demfit_mom_xit_t0cut", "demfit.sid==2 && demlh.t0>=700", "goff");

  // resolution histograms
  ntuple->Draw("(demfit[][demmcvd.iinter].mom.R() - demmcvd[].mom.R())>>h_demfit_momres_all", "", "goff");
  ntuple->Draw("(demfit[][demmcvd.iinter].mom.R() - demmcvd[].mom.R())>>h_demfit_momres_ent", "demmcvd[].sid==0", "goff");
  ntuple->Draw("(demfit[][demmcvd.iinter].mom.R() - demmcvd[].mom.R())>>h_demfit_momres_mid", "demmcvd[].sid==1", "goff");
  ntuple->Draw("(demfit[][demmcvd.iinter].mom.R() - demmcvd[].mom.R())>>h_demfit_momres_xit", "demmcvd[].sid==2", "goff");

  // trkcalohit histograms
  ntuple->Draw("demtch.ctime>>h_demtch_ctime_all", "", "goff");
  ntuple->Draw("demtch.ctime>>h_demtch_ctime_active", "demtch.active==1", "goff");
  ntuple->Draw("demtch.ctime>>h_demtch_ctime_inactive", "demtch.active==0", "goff");
  ntuple->Draw("demtch.ctime-demlh.t0>>h_demtch_demfit_dt_ent", "demfit.sid==0 && demtch.active==1", "goff");

  // crv histograms
  ntuple->Draw("crvsummary.totalPEs>>h_crvsummary_totalPEs_all", "", "goff");
  ntuple->Draw("crvcoincs.pos.fCoordinates.fX>>h_crvhit_pos_x", "", "goff");
  ntuple->Draw("crvcoincs.pos.fCoordinates.fY>>h_crvhit_pos_y", "", "goff");
  ntuple->Draw("crvcoincs.pos.fCoordinates.fZ>>h_crvhit_pos_z", "", "goff");
  ntuple->Draw("crvcoincsmc.primary.fCoordinates.fX>>h_crvhitmc_primary_x", "", "goff");
  ntuple->Draw("crvcoincsmc.primary.fCoordinates.fY>>h_crvhitmc_primary_y", "", "goff");
  ntuple->Draw("crvcoincsmc.primary.fCoordinates.fZ>>h_crvhitmc_primary_z", "", "goff");
  ntuple->Draw("crvcoincsmc.depositedEnergy>>h_crvhitmc_depostedEnergy", "", "goff");

  // demmcsim histograms
  ntuple->Draw("demmcsim.pos.x()>>h_demmcsim_pos_x_all", "", "goff");
  ntuple->Draw("demmcsim.pos.y()>>h_demmcsim_pos_y_all", "", "goff");
  ntuple->Draw("demmcsim.pos.z()>>h_demmcsim_pos_z_all", "", "goff");
  ntuple->Draw("demmcsim.pos.x()>>h_demmcsim_pos_x_evtprimary", "demmcsim.prirel._rel==0 && demmcsim.prirel._rem==0", "goff");
  ntuple->Draw("demmcsim.pos.y()>>h_demmcsim_pos_y_evtprimary", "demmcsim.prirel._rel==0 && demmcsim.prirel._rem==0", "goff");
  ntuple->Draw("demmcsim.pos.z()>>h_demmcsim_pos_z_evtprimary", "demmcsim.prirel._rel==0 && demmcsim.prirel._rem==0", "goff");
  ntuple->Draw("demmcsim.pos.x()>>h_demmcsim_pos_x_trkprimary", "demmcsim.trkrel._rel==0 && demmcsim.trkrel._rem==0", "goff");
  ntuple->Draw("demmcsim.pos.y()>>h_demmcsim_pos_y_trkprimary", "demmcsim.trkrel._rel==0 && demmcsim.trkrel._rem==0", "goff");
  ntuple->Draw("demmcsim.pos.z()>>h_demmcsim_pos_z_trkprimary", "demmcsim.trkrel._rel==0 && demmcsim.trkrel._rem==0", "goff");
  ntuple->Draw("demmcsim.pos.x()>>h_demmcsim_pos_x_trkparent", "demmcsim.trkrel._rel==2 && demmcsim.trkrel._rem==1", "goff");
  ntuple->Draw("demmcsim.pos.y()>>h_demmcsim_pos_y_trkparent", "demmcsim.trkrel._rel==2 && demmcsim.trkrel._rem==1", "goff");
  ntuple->Draw("demmcsim.pos.z()>>h_demmcsim_pos_z_trkparent", "demmcsim.trkrel._rel==2 && demmcsim.trkrel._rem==1", "goff");
  ntuple->Draw("demmcsim.pos.x()>>h_demmcsim_pos_x_trkgparent", "demmcsim.trkrel._rel==5 && demmcsim.trkrel._rem==2", "goff");
  ntuple->Draw("demmcsim.pos.y()>>h_demmcsim_pos_y_trkgparent", "demmcsim.trkrel._rel==5 && demmcsim.trkrel._rem==2", "goff");
  ntuple->Draw("demmcsim.pos.z()>>h_demmcsim_pos_z_trkgparent", "demmcsim.trkrel._rel==5 && demmcsim.trkrel._rem==2", "goff");
  ntuple->Draw("demmcsim.pos.x()>>h_demmcsim_pos_x_trkggparent", "demmcsim.trkrel._rel==5 && demmcsim.trkrel._rem==3", "goff");
  ntuple->Draw("demmcsim.pos.y()>>h_demmcsim_pos_y_trkggparent", "demmcsim.trkrel._rel==5 && demmcsim.trkrel._rem==3", "goff");
  ntuple->Draw("demmcsim.pos.z()>>h_demmcsim_pos_z_trkggparent", "demmcsim.trkrel._rel==5 && demmcsim.trkrel._rem==3", "goff");


  file->Write();
  file->Close();
}
