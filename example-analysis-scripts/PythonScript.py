#
# To run (on a mu2egpvm machine):
# > setup mu2e
# > muse setup TrkAna
# > setup pyana v1_04_00
# > python TrkAna/example-analysis-scripts/PythonScript.py
#
import uproot
import matplotlib.pyplot as plt
import numpy as np
import awkward as ak

# The script will start here
# Open the file, grab the trkana tree and show it
filename = "nts.owner.trkana-reco.version.sequencer.root"
dirname = "TrkAnaNeg"
treename = "trkana"
file = uproot.open(filename)
trkana = file[dirname][treename]

dement_mom=[] # reco momentum at tracker entrance
dement_t0=[]
# To help deal with potentially large files, we will process the data in 'batches'
for batch, report in trkana.iterate(step_size="10 MB", filter_name="/de*/i", report=True, library='ak'):

    batch['demfit.mom'] = (batch['demfit.mom.fCoordinates.fX']**2 + batch['demfit.mom.fCoordinates.fY']**2 + batch['demfit.mom.fCoordinates.fZ']**2)**0.5

    # Because demfit is an array of fit results at different positions along the track,
    # we need to make sure that we only get the results for the tracker entrance (sid=0).
    #
    # i.e. We have:
    #   demfit = [ [ trk1_ent, trk1_mid, trk1_xit ], [ trk2_ent, trk2_mid, trk2_xit ], ... [ trkN_ent, trkN_mid, trkN_xit ] ]
    #   demfit.mom = [ [ trk1_entmom, trk1_midmom, trk1_xitmom ], [ trk2_entmom, trk2_midmom, trk2_xitmom ], ... [ trkN_entmom, trkN_midmom, trkN_xitmom ] ]
    #   demfit.sid = [ [ 0, 1, 2 ], [ 0, 1, 2 ], ... [ 0, 1, 2 ] ]
    #
    # To handle this we make a mask:
    fit_mask = (batch['demfit.sid']==0)
    # which looks like this
    #   fit_mask = [ [ True, False, False ], [ True, False, False ], ... [ True, False, False ] ]
    #
    # We then apply the mask to the "demfit.mom"
    masked_dement_mom = batch['demfit.mom'][fit_mask]
    # which looks like this
    #   masked_dement_mom = [ [ trk1_entmom ], [ trk2_entmom ], ... [ trkN_entmom ] ]
    #
    # Note that we still have 2 array dimensions so we need to flatten it out
    flattened_dement_mom = ak.flatten(masked_dement_mom)
    # which looks like this
    #   flattened_dement_mom = [ trk1_entmom, trk2_entmom, ..., trkN_entmom ]
    #
    # Then we convert to a numpy array and add it to the full array of data
    dement_mom = np.append(dement_mom, flattened_dement_mom.to_numpy())

    # Do the above in one line for time
    dement_t0 = np.append(dement_t0, ak.flatten(batch['demlh.t0'][fit_mask]).to_numpy())

# Create a figure to put our plots on
fig, ax = plt.subplots(1,1)

# Create a histogram of all the tracks
min_mom=90
max_mom=110
mom_bin_width=0.2
n_mom_bins=int((max_mom - min_mom) / mom_bin_width)
content, edges, patches = ax.hist(dement_mom,
                                  bins=n_mom_bins,
                                  range=(min_mom,max_mom),
                                  label="all tracks",
                                  histtype='step')

content, edges, patches = ax.hist(dement_mom[(dement_t0>700)],
                                  bins=n_mom_bins,
                                  range=(min_mom,max_mom),
                                  label="t0 > 700",
                                  histtype='step')


ax.legend()
ax.set_xlabel('Reco Momentum [MeV/c]')
ax.set_ylabel('No. of Tracks')
ax.grid(True)
plt.show()
