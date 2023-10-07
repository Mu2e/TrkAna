#include "TCut.h"
#include "TTree.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TProfile.h"
#include "TCanvas.h"
#include "TDirectory.h"
#include "THStack.h"
#include "TStyle.h"
#include <iostream>
#include <fstream>
#include <string>
#include "TChain.h"

void FillChain(TChain* chain,const char* files, bool verbose=false){
  cout << "filling chain for tree " << chain->GetName() << " from files in " << files << endl;
  ifstream ifs(files);
  if(ifs.is_open()){
    string file;
    while(getline(ifs,file)){
      if(verbose)cout << "adding file " << file << endl;
      chain->Add(file.c_str());
    }
    ifs.close();
  } else
    cout << "File " << files << " can't be opened, aborting" << endl;
}

void CrvExtracted(const char* filelist){
  TChain* extchain = new TChain("TrkAnaExt/trkana");
  FillChain(extchain,filelist,true);
  TCut goodtrk("kl.status>0");
  TCut CRV1("crvhit[0].sectorType==1");
  TCut KLCRV1("klfit.sid==200&&klfit.sindex==1");
  TCut bestfit("klkl.z0err<1&&klkl.d0err<1&&klkl.thetaerr<0.0004&&klkl.phi0err<0.001&&kl.ndof>=10&&kl.fitcon>0.1&&kl.nactive/kl.nhits>0.99&&kl.nplanes>=4&&kl.nnullambig/kl.nhits<0.2");
  TCut goodCRV("crvhit[0].nHits>0");
  TCut noCRV("crvsummary.nHitCounters==0");
  TCut L1Fiducial("abs(klfit.pos.X())<2500 && fabs(klfit.pos.Z()+500)<1500");
  TH2D* tcrvpg = new TH2D("tcrvpg","KKInter TCRV Layer 1 Position, Has CRVCoincidence;KKInter Z (mm);KKInter X (mm)",100,-8000,8000,100,-8000,8000);
  TH2D* tcrvpb = new TH2D("tcrvpb","KKInter TCRV Layer 1 Position,  No CRVCoincidence;KKInter Z (mm);KKInter X (mm)",100,-8000,8000,100,-8000,8000);
  tcrvpg->SetStats(0);
  tcrvpb->SetStats(0);

  TH1D* tcrvts = new TH1D("tcrvts","KKInter Time - CRV Time, Layer 1 #Delta T;T_{KKInter} - T_{CRV} (ns)",250,-30,30);

  TH1D* tcrvy = new TH1D("tcrvy","KKInter TCRV Layer 1 #Delta Y;Y_{KKInter} - Y_{CRV} (mm)",100,-50,50);

  TH2D* dtvx = new TH2D("dtvx","KKInter TCRV Layer 1 #Delta T vs X;KKInter X (mm);T_{KKInter}-T_{CRV} (ns)",50,-3400,3400,100,-15,15);
  TH2D* dtvz = new TH2D("dtvz","KKInter TCRV Layer 1 #Delta T vs Z;KKInter Z (mm);T_{KKInter}-T_{CRV} (ns)",50,-2500,1500,100,-15,15);
  TH2D* xvx = new TH2D("xvx","CRV Layer1 X vs KKInter X;KKInter X (mm);CRV X (mm)",50,-3400,3400,50,-3400,3400);
  TH2D* zvz = new TH2D("zvz","CRV Layer1 Z vs KKInter Z;KKInter Z (mm);CRV Z (mm)",50,-2500,1500,50,11500,15500);
  dtvx->SetStats(0);
  dtvz->SetStats(0);
  xvx->SetStats(0);
  zvz->SetStats(0);

  tcrvts->SetLineColor(kBlue);

  extchain->Project("tcrvpg","klfit.pos.X():klfit.pos.Z()",goodtrk+KLCRV1+CRV1+bestfit+goodCRV);
  extchain->Project("tcrvpb","klfit.pos.X():klfit.pos.Z()",goodtrk+KLCRV1+bestfit+noCRV);
  extchain->Project("tcrvy","klfit.pos.Y()-crvhit[0].pos.Y()",goodtrk+KLCRV1+CRV1+bestfit+goodCRV);
  extchain->Project("tcrvts","klfit.time-crvhit[0].time",goodtrk+KLCRV1+CRV1+bestfit+goodCRV);
  extchain->Project("dtvz","klfit.time-crvhit[0].time:klfit.pos.Z()",goodtrk+KLCRV1+CRV1+bestfit+goodCRV);
  extchain->Project("dtvx","klfit.time-crvhit[0].time:klfit.pos.X()",goodtrk+KLCRV1+CRV1+bestfit+goodCRV);
  extchain->Project("xvx","crvhit[0].pos.X():klfit.pos.X()",goodtrk+KLCRV1+CRV1+bestfit+goodCRV);
  extchain->Project("zvz","crvhit[0].pos.Z():klfit.pos.Z()",goodtrk+KLCRV1+CRV1+bestfit+goodCRV);

  TCanvas* tcan = new TCanvas("tcan","tcan",1200,1200);
  tcan->Divide(2,2);
  tcan->cd(1);
  tcrvts->Fit("gaus");
  tcan->cd(3);
  gPad->SetLogz();
  zvz->Draw("colorz");
  tcan->cd(2);
  gPad->SetLogz();
  dtvx->Draw("colorz");
  tcan->cd(4);
  gPad->SetLogz();
  xvx->Draw("colorz");

  TCanvas* pcan = new TCanvas("pcan","pcan",1200,800);
  pcan->Divide(2,1);
  pcan->cd(1);
  gPad->SetLogz();
  tcrvpg->Draw("colorz");
  pcan->cd(2);
  gPad->SetLogz();
  tcrvpb->Draw("colorz");

}

