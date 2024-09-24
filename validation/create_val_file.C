void create_val_file(std::string filename, std::string outfilename) {

  TFile* ntuple_file = new TFile(filename.c_str(), "READ");
  TTree* ntuple = (TTree*) ntuple_file->Get("EventNtuple/ntuple");

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

  // trkfit histograms
  ntuple->Draw("trkfit.mom.R()>>h_demfit_mom_all", "", "goff");
  ntuple->Draw("trkfit.mom.R()>>h_demfit_mom_ent", "trkfit.sid==0", "goff");
  ntuple->Draw("trkfit.mom.R()>>h_demfit_mom_mid", "trkfit.sid==1", "goff");
  ntuple->Draw("trkfit.mom.R()>>h_demfit_mom_xit", "trkfit.sid==2", "goff");
  ntuple->Draw("trkfit.mom.R()>>h_demfit_mom_ent_t0cut", "trkfit.sid==0 && trklh.t0>=700", "goff");
  ntuple->Draw("trkfit.mom.R()>>h_demfit_mom_mid_t0cut", "trkfit.sid==1 && trklh.t0>=700", "goff");
  ntuple->Draw("trkfit.mom.R()>>h_demfit_mom_xit_t0cut", "trkfit.sid==2 && trklh.t0>=700", "goff");

  // resolution histograms
  ntuple->Draw("(trkfit[][trkmcvd.iinter].mom.R() - trkmcvd[].mom.R())>>h_demfit_momres_all", "", "goff");
  ntuple->Draw("(trkfit[][trkmcvd.iinter].mom.R() - trkmcvd[].mom.R())>>h_demfit_momres_ent", "trkmcvd[].sid==0", "goff");
  ntuple->Draw("(trkfit[][trkmcvd.iinter].mom.R() - trkmcvd[].mom.R())>>h_demfit_momres_mid", "trkmcvd[].sid==1", "goff");
  ntuple->Draw("(trkfit[][trkmcvd.iinter].mom.R() - trkmcvd[].mom.R())>>h_demfit_momres_xit", "trkmcvd[].sid==2", "goff");

  // trkcalohit histograms
  ntuple->Draw("trktch.ctime>>h_demtch_ctime_all", "", "goff");
  ntuple->Draw("trktch.ctime>>h_demtch_ctime_active", "trktch.active==1", "goff");
  ntuple->Draw("trktch.ctime>>h_demtch_ctime_inactive", "trktch.active==0", "goff");
  ntuple->Draw("trktch.ctime-trklh.t0>>h_demtch_demfit_dt_ent", "trkfit.sid==0 && trktch.active==1", "goff");

  // crv histograms
  ntuple->Draw("crvsummary.totalPEs>>h_crvsummary_totalPEs_all", "", "goff");
  ntuple->Draw("crvcoincs.pos.fCoordinates.fX>>h_crvhit_pos_x", "", "goff");
  ntuple->Draw("crvcoincs.pos.fCoordinates.fY>>h_crvhit_pos_y", "", "goff");
  ntuple->Draw("crvcoincs.pos.fCoordinates.fZ>>h_crvhit_pos_z", "", "goff");
  ntuple->Draw("crvcoincsmc.primary.fCoordinates.fX>>h_crvhitmc_primary_x", "", "goff");
  ntuple->Draw("crvcoincsmc.primary.fCoordinates.fY>>h_crvhitmc_primary_y", "", "goff");
  ntuple->Draw("crvcoincsmc.primary.fCoordinates.fZ>>h_crvhitmc_primary_z", "", "goff");
  ntuple->Draw("crvcoincsmc.depositedEnergy>>h_crvhitmc_depostedEnergy", "", "goff");

  // trkmcsim histograms
  ntuple->Draw("trkmcsim.pos.x()>>h_demmcsim_pos_x_all", "", "goff");
  ntuple->Draw("trkmcsim.pos.y()>>h_demmcsim_pos_y_all", "", "goff");
  ntuple->Draw("trkmcsim.pos.z()>>h_demmcsim_pos_z_all", "", "goff");
  ntuple->Draw("trkmcsim.pos.x()>>h_demmcsim_pos_x_evtprimary", "trkmcsim.prirel._rel==0 && trkmcsim.prirel._rem==0", "goff");
  ntuple->Draw("trkmcsim.pos.y()>>h_demmcsim_pos_y_evtprimary", "trkmcsim.prirel._rel==0 && trkmcsim.prirel._rem==0", "goff");
  ntuple->Draw("trkmcsim.pos.z()>>h_demmcsim_pos_z_evtprimary", "trkmcsim.prirel._rel==0 && trkmcsim.prirel._rem==0", "goff");
  ntuple->Draw("trkmcsim.pos.x()>>h_demmcsim_pos_x_trkprimary", "trkmcsim.trkrel._rel==0 && trkmcsim.trkrel._rem==0", "goff");
  ntuple->Draw("trkmcsim.pos.y()>>h_demmcsim_pos_y_trkprimary", "trkmcsim.trkrel._rel==0 && trkmcsim.trkrel._rem==0", "goff");
  ntuple->Draw("trkmcsim.pos.z()>>h_demmcsim_pos_z_trkprimary", "trkmcsim.trkrel._rel==0 && trkmcsim.trkrel._rem==0", "goff");
  ntuple->Draw("trkmcsim.pos.x()>>h_demmcsim_pos_x_trkparent", "trkmcsim.trkrel._rel==2 && trkmcsim.trkrel._rem==1", "goff");
  ntuple->Draw("trkmcsim.pos.y()>>h_demmcsim_pos_y_trkparent", "trkmcsim.trkrel._rel==2 && trkmcsim.trkrel._rem==1", "goff");
  ntuple->Draw("trkmcsim.pos.z()>>h_demmcsim_pos_z_trkparent", "trkmcsim.trkrel._rel==2 && trkmcsim.trkrel._rem==1", "goff");
  ntuple->Draw("trkmcsim.pos.x()>>h_demmcsim_pos_x_trkgparent", "trkmcsim.trkrel._rel==5 && trkmcsim.trkrel._rem==2", "goff");
  ntuple->Draw("trkmcsim.pos.y()>>h_demmcsim_pos_y_trkgparent", "trkmcsim.trkrel._rel==5 && trkmcsim.trkrel._rem==2", "goff");
  ntuple->Draw("trkmcsim.pos.z()>>h_demmcsim_pos_z_trkgparent", "trkmcsim.trkrel._rel==5 && trkmcsim.trkrel._rem==2", "goff");
  ntuple->Draw("trkmcsim.pos.x()>>h_demmcsim_pos_x_trkggparent", "trkmcsim.trkrel._rel==5 && trkmcsim.trkrel._rem==3", "goff");
  ntuple->Draw("trkmcsim.pos.y()>>h_demmcsim_pos_y_trkggparent", "trkmcsim.trkrel._rel==5 && trkmcsim.trkrel._rem==3", "goff");
  ntuple->Draw("trkmcsim.pos.z()>>h_demmcsim_pos_z_trkggparent", "trkmcsim.trkrel._rel==5 && trkmcsim.trkrel._rem==3", "goff");


  file->Write();
  file->Close();
}
