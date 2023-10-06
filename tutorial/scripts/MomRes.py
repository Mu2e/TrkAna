import sys
import uproot # for reading in ROOT files
import matplotlib.pyplot as plt # for making plots
import numpy as np
import awkward as ak

filename=sys.argv[1]
treename="TrkAnaNeg/trkana"

trk_ent_mom=[]
mc_trk_ent_mom=[]
for batch, report in uproot.iterate(files=filename+":"+treename, filter_name=["/demfit[.]*/", "/demlh[.]*/", "/demmcvd[.]*/"], step_size="10 MB", report=True):
    print(report)

    batch['demfit.mom'] = (batch['demfit.mom.fCoordinates.fX']**2 + batch['demfit.mom.fCoordinates.fY']**2 + batch['demfit.mom.fCoordinates.fZ']**2)**0.5
    batch['demmcvd.mom'] = (batch['demmcvd.mom.fCoordinates.fX']**2 + batch['demmcvd.mom.fCoordinates.fY']**2 + batch['demmcvd.mom.fCoordinates.fZ']**2)**0.5

    trk_ent_mask = (batch['demfit.sid']==0)
    has_trk_ent = ak.flatten(ak.any(trk_ent_mask, axis=1, keepdims=True))

    mc_trk_ent_mask = (batch['demmcvd.sid']==0)
    has_mc_trk_ent = ak.flatten(ak.any(mc_trk_ent_mask, axis=1, keepdims=True))

    has_both = (has_trk_ent) & (has_mc_trk_ent)

    trk_ent_mom = np.append(trk_ent_mom, ak.flatten(batch['demfit.mom'][(has_both) & (trk_ent_mask)]))
    mc_trk_ent_mom = np.append(mc_trk_ent_mom, ak.flatten(batch['demmcvd.mom'][(has_both) & (mc_trk_ent_mask)]))


fig, ax = plt.subplots(1,1)

mom_res = trk_ent_mom - mc_trk_ent_mom

min_mom_res = -4
max_mom_res = 4
mom_res_bin_width = 0.05
n_mom_res_bins = int((max_mom_res - min_mom_res) / mom_res_bin_width)

ax.hist(mom_res, bins=n_mom_res_bins, range=(min_mom_res,max_mom_res), label='all tracks', histtype='step', log=True)
#ax.hist(ak.flatten(batch['demfit.mom'][(trk_ent_mask) & (time_cut_mask)]), bins=n_mom_res_bins, range=(min_mom_res,max_mom_res), label='t0>=700', histtype='step')

ax.legend()
ax.set_xlabel('Momentum Resolution at Tracker Entrance [MeV/c]')
ax.set_ylabel('Number of Tracks')
ax.grid(True)
ax.margins(0)
plt.show()
