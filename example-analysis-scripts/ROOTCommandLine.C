// For data exploration, it is often easier to open the file with ROOT and investigate on the command line.
// In this example, you can either follow the steps below or you can run this script like so:
//
// > root -l TrkAna/example-analysis-scripts/ROOTCommandLine.C
//
/////////////////////////
// First, open the trkana file with ROOT:
//
// > root -l nts.owner.trkana-reco.version.sequencer.root
//
// Then we change directory into the TrkAnaNeg folder:
//
// > TrkAnaNeg->cd()
//
// Then we can print the branches and leaves of the tree:
//
// > trkana->Print()
//
// We can also create histograms from the tree
//
// > trkana->Draw("demfit[0].mom.R()>>hist(100,90,110)")
//
// and change its line colour
//
// > hist->SetLineColor(kRed)
//
// and then draw another histogram with a cut on time
//
// > trkana->Draw("demfit[0].mom.R()>>hist(100,90,110)", "demlh[0].t0>700", "HIST SAME")
//
// Finally, one can Scan through the tree event by event:
//
// > trkana->Scan("demfit[0].mom.R():demlh[0].t0", "de.t0>700")
//
{
  gROOT->ProcessLine("TFile* file = new TFile(\"nts.owner.trkana-reco.version.sequencer.root\", \"READ\")");;
  gROOT->ProcessLine("TrkAnaNeg->cd()");
  gROOT->ProcessLine("trkana->Print()");
  gROOT->ProcessLine("trkana->Draw(\"demfit[0].mom.R()>>hist(100,90,110)\")");
  gROOT->ProcessLine("hist->SetLineColor(kRed)");
  gROOT->ProcessLine("trkana->Draw(\"demfit[0].mom.R()>>hist2(100,90,110)\", \"demlh[0].t0>700\", \"HIST SAME\")");
  gROOT->ProcessLine("trkana->Scan(\"demfit[0].mom.R():demlh[0].t0\", \"demlh[0].t0>700\")");
}
