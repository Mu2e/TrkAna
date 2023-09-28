import uproot # for reading in ROOT files
import matplotlib.pyplot as plt # for making plots
import awkward as ak

filename="nts.brownd.CeEndpointMix1BBSignal.MDC2020z_TKAv04.tka"
treename="TrkAnaNeg/trkana"

# Open the ROOT file and be read yto read in the trkana tree
trkana = uproot.open(filename+":"+treename)

# Read in just the dem. branch
branches = trkana.arrays(filter_name=["/demfit[.]*/", "/demlh[.]*/"])

branches['demfit.mom'] = (branches['demfit.mom.fCoordinates.fX']**2 + branches['demfit.mom.fCoordinates.fY']**2 + branches['demfit.mom.fCoordinates.fZ']**2)**0.5

fig, ax = plt.subplots(1,1)

trk_ent_mask = (branches['demfit.sid']==0)
time_cut_mask = (branches['demlh.t0']>=700)

min_mom = 100
max_mom = 107
mom_bin_width = 0.1
n_mom_bins = int((max_mom - min_mom) / mom_bin_width)

ax.hist(ak.flatten(branches['demfit.mom'][(trk_ent_mask)]), bins=n_mom_bins, range=(min_mom,max_mom), label='all tracks', histtype='step')
ax.hist(ak.flatten(branches['demfit.mom'][(trk_ent_mask) & (time_cut_mask)]), bins=n_mom_bins, range=(min_mom,max_mom), label='t0>=700', histtype='step')

ax.legend()
ax.set_xlabel('Reconstructed Momentum at Tracker Entrance [MeV/c]')
ax.set_ylabel('Number of Tracks')
ax.grid(True)
plt.show()
