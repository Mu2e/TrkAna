# In this example, we use PyROOT to generate a cut flow report and plot it
# To run:
#  > python TrkAna/examples/PyROOTRDataFrame.py
import ROOT
import math

filename = "nts.owner.trkana-reco.version.sequencer.root"
treename = "TrkAnaNeg/trkana"
d = ROOT.RDataFrame(treename, filename)

# Define all the cuts
all_cuts = { 'status' : 'de.status>0',
             't0' : 'de.t0>700 && de.t0<1695',
             'tandip' : 'deent.td>0.577350 && deent.td<1.000',
             'd0' : 'deent.d0>-80 && deent.d0<105',
             'max_radius' : 'deent.d0+2./deent.om>450 && deent.d0+2./deent.om<680',
             'CRV' : '(bestcrv<0||(de.t0-crvinfo._timeWindowStart[bestcrv]<-50||de.t0-crvinfo._timeWindowStart[bestcrv]>150.0))',
             'TrkQual' : 'dequal.TrkQual>0.8',
             'TrkPID' : 'dequal.TrkPID>0.95',
             'upstream' : 'ue.status<=0'
}

# Apply all the cuts in turn
filt1 = d
for name, cut in all_cuts.items():
    filt1 = filt1.Filter(cut, name)

# Get a CutFlow report and plot it
filt1.Report()
allCutsReport = d.Report()
allCutsReport.Print()
hCutFlow = ROOT.TH1D("hCutFlow", "Cut Flow", 10,0,10)
i_bin=1
for cut in allCutsReport:
    hCutFlow.GetXaxis().SetBinLabel(i_bin, cut.GetName())
    hCutFlow.SetBinContent(i_bin, cut.GetPass())
    hCutFlow.SetBinError(i_bin, math.sqrt(cut.GetPass()))
    i_bin=i_bin+1

c_cutFlow = ROOT.TCanvas('c_cutFlow', 'c_cutFlow')
#hCutFlow.Scale(1.0/990000)
#hCutFlow.Scale(1.0/200000)
#hCutFlow.Scale(1.0/1100000.0)
hCutFlow.Scale(1.0/380000)
hCutFlow.SetMarkerSize(2);
hCutFlow.Draw("HIST TEXT 90")
c_cutFlow.Update()

# # Plot the momentum of the original and cut
# c_hist = ROOT.TCanvas('c_hist', 'c_hist')
# hist_all = d.Histo1D({"", "", 100,90.,110.}, "deent.mom")
# hist_cut = filt1.Histo1D({"", "", 100,90.,110.}, "deent.mom")
# hist_all.SetLineColor(ROOT.kBlue)
# hist_cut.SetLineColor(ROOT.kRed)
# hist_all.Draw("HIST E")
# hist_cut.Draw("SAME")
# c_hist.Update()

# keep the canvases open
ROOT.gApplication.Run()
