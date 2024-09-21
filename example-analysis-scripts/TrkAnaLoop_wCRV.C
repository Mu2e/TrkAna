//
// This macro gives an example of looping through the TrkAna tree
//

#include "TrkAna/inc/TrkInfo.hh"
#include "TrkAna/inc/CrvHitInfoReco.hh"

#include "TFile.h"
#include "TTree.h"
#include "TH1F.h"

void TrkAnaLoop(std::string filename) {

  TFile* file = new TFile(filename.c_str(), "READ");
  TTree* trkana = (TTree*) file->Get("TrkAna/trkana");

  std::vector<std::vector<mu2e::TrkFitInfo> >* tracks = nullptr;
  trkana->SetBranchAddress("demfit", &tracks);

  std::vector<mu2e::CrvHitInfoReco>* crvcoincs = nullptr;
  trkana->SetBranchAddress("crvcoincs", &crvcoincs);

  TH1F* hRecoMom = new TH1F("hRecoMom", "", 15,95,110);
  TH1F* hRecoMom_crvCut = new TH1F("hRecoMom_crvCut", "", 15,95,110);

  int n_events = trkana->GetEntries();
  for (int i_event = 0; i_event < n_events; ++i_event) {
    trkana->GetEntry(i_event);

    for (auto& track : *tracks) {
      for (auto& fit : track) {
        if (fit.sid == 0) {
          double track_time = fit.time;
          hRecoMom->Fill(fit.mom.R());

          bool crvhit = false;
          for (auto& crvcoinc : *crvcoincs) {
            double crvcoinc_time = crvcoinc.time;
            if (std::fabs(crvcoinc_time - track_time) < 100) {
              crvhit = true;
            }
          }
          if (!crvhit) {
            hRecoMom_crvCut->Fill(fit.mom.R());
          }
        }
      }
    }
  }

  hRecoMom->Draw("HIST E");
  hRecoMom_crvCut->SetLineColor(kRed);
  hRecoMom_crvCut->Draw("HIST E SAME");
}
