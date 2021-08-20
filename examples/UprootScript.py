#
# Adapated from the example in the Mu2e Wiki here: https://mu2ewiki.fnal.gov/wiki/TrkAna#Python (Thanks, Roberto!)
#
# To run: python TrkAna/examples/UprootScript.py
#
import numpy as np
import awkward as ak
import uproot
import matplotlib.pyplot as plt

#Open the file, grab the trkana tree and show it
filename = "nts.owner.trkana-reco.version.sequencer.root"
dirname = "TrkAnaNeg"
treename = "trkana"
file = uproot.open(filename)
trkana = file[dirname][treename]
trkana.show()

trkana_ak = trkana.arrays(library='ak')#, entry_stop=100) # Read the trkana tree into an awkward array

ak_draw = trkana_ak["deent"]["mom"] # Get the array of values we want to plot

#print(trkana.keys(filter_name="/qual/"))
#print(trkana_ak["dequal"][0])
#print(trkana_ak["crvinfo._timeWindowStart"][8])
# Get masks (array of True/False) for every cut
cuts = { 'status' : trkana_ak["de"]["status"]>0,
         't0' : (trkana_ak["de"]["t0"]>700) & (trkana_ak["de"]["t0"]<1695),
         'tandip' : (trkana_ak["deent"]["td"]>0.577350) & (trkana_ak["deent"]["td"]<1.000),
         'd0' : (trkana_ak["deent"]["d0"]>-80) & (trkana_ak["deent"]["d0"]<105),
         'max_radius' : (trkana_ak["deent"]["d0"]+2./trkana_ak["deent"]["om"]>450) & (trkana_ak["deent"]["d0"]+2./trkana_ak["deent"]["om"]<680),
#(trkana_ak["bestcrv"]<0) |
#         'CRV' :  (trkana_ak["de"]["t0"]-trkana_ak["crvinfo._timeWindowStart"])#[trkana_ak["bestcrv"]]<-50) # ||de.t0-crvinfo._timeWindowStart[bestcrv]>150.0))',
         'TrkQual' : trkana_ak["dequal"]["TrkQual"]>0.8,
         'TrkPID' : trkana_ak["dequal"]["TrkPID"]>0.95,
         'upstream' : trkana_ak["ue"]["status"]<=0
}
print(cuts)
all_cuts = ak.Array(np.ones(shape=len(ak_draw), dtype=bool)) # set to all true to start with
print(all_cuts)

n_gen_events=file["genCountLogger/numEvents"].values()[0]
effs={}
eff_errs={}
for name, cut in cuts.items():
    all_cuts = all_cuts & cut # take the AND of all cuts
    print(name + " " + str(sum(cut)) + " " + str(sum(all_cuts)))
    effs[name] = sum(all_cuts) / n_gen_events
    eff_errs[name] = np.sqrt(sum(all_cuts)) / n_gen_events

print(effs)

# Define histogram parameters
min_mom = 90
max_mom = 110
bin_width = 0.2
n_bins = int((max_mom - min_mom) / bin_width)

# Draw histograms
fig, ax = plt.subplots(1,1)
n, bins, patches = ax.hist(ak_draw,
                           bins=n_bins, 
                           range=(min_mom,max_mom), 
                           label="all tracks",
                           histtype='step')
n, bins, patches = ax.hist(ak_draw[all_cuts],
                           bins=n_bins, 
                           range=(min_mom,max_mom), 
                           label="MDC2018 Cuts",
                           histtype='step')

ax.legend()
plt.show()

fig, ax = plt.subplots(1,1, figsize=(8,4))
p1 = ax.bar(effs.keys(), effs.values(), fill=False)
ax.bar_label(p1, labels=[' %.3f\n±%.3f' % (v,e) for (v,e) in zip(effs.values(), eff_errs.values())])
ax.errorbar(effs.keys(), effs.values(), yerr=eff_errs.values(), fmt='o', color='black')
#plt.xticks(rotation=45, ha='center', va='center')
ax.set_title('MDC2018 Cuts')
plt.ylabel('Efficiency')
#plt.grid(axis='y')
plt.show()

