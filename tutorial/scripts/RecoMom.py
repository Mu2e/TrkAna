import sys
import uproot # for reading in ROOT files
import matplotlib.pyplot as plt # for making plots
import numpy as np
import awkward as ak

filename=sys.argv[1]
treename="TrkAna/trkana"

# Get ready for iterating
demfit_all_mom=[]
demfit_ent_mom=[]
demfit_ent_mom_timecut=[]
for batch, report in uproot.iterate(files=filename+":"+treename, filter_name=["/demfit/", "/demlh/"], step_size="10 MB", report=True):
    print(batch['demfit']['mom']['fCoordinates'].fields)
    print(report)
    batch['demfit_mom'] = np.sqrt((batch['demfit']['mom']['fCoordinates']['fX'])**2 + (batch['demfit']['mom']['fCoordinates']['fY'])**2 + (batch['demfit']['mom']['fCoordinates']['fZ'])**2)

    demfit_all_mom = np.append(demfit_ent_mom, ak.flatten(batch['demfit_mom']))
    trk_ent_mask = (batch['demfit']['sid']==0)
    time_cut_mask = (batch['demlh']['t0']>=700)

    demfit_ent_mom = np.append(demfit_ent_mom, ak.flatten(batch[(trk_ent_mask)]['demfit_mom']))
    demfit_ent_mom_timecut = np.append(demfit_ent_mom_timecut, ak.flatten(batch[(trk_ent_mask) & (time_cut_mask)]['demfit_mom'], axis=None))

fig, ax = plt.subplots(1,1)

min_mom = 100
max_mom = 107
mom_bin_width = 0.1
n_mom_bins = int((max_mom - min_mom) / mom_bin_width)

ax.hist(demfit_all_mom, bins=n_mom_bins, range=(min_mom,max_mom), label='all fits', histtype='step')
ax.hist(demfit_ent_mom, bins=n_mom_bins, range=(min_mom,max_mom), label='ent fits', histtype='step')
ax.hist(demfit_ent_mom_timecut, bins=n_mom_bins, range=(min_mom,max_mom), label='ent fits with t0>=700', histtype='step')

ax.legend()
ax.set_xlabel('Reconstructed Momentum at Tracker Entrance [MeV/c]')
ax.set_ylabel('Number of Tracks')
ax.grid(True)
plt.show()
