#
# To run (on a mu2egpvm machine):
# > setup mu2e
# > muse setup TrkAna
# > setup pyana v1_05_00
# > python TrkAna/example-analysis-scripts/Genealogy.py
#
import uproot
import matplotlib.pyplot as plt
import numpy as np
import awkward as ak
import MCDataProducts # for process codes etc.

# Define two useful functions
def add_useful_columns(batch): # will calculate some useful values
    batch['demmcsim.mom'] = (batch['demmcsim.mom.fCoordinates.fX']**2 + batch['demmcsim.mom.fCoordinates.fY']**2 + batch['demmcsim.mom.fCoordinates.fZ']**2)**0.5

def zip_branches(batch): # will return a reduced awkward array with the branches we want
    cols = ['demmcsim.mom', 'demmcsim.pdg', 'demmcsim.trkrel._rem', 'demmcsim.gen']
    return ak.zip({col : batch[col] for col in cols})

# The script will start here
# Open the file and grab the trkana tree
filename = "nts.owner.trkana-reco.version.sequencer.root"
dirname = "TrkAnaNeg"
treename = "trkana"
trkana = uproot.open(filename+":"+dirname+"/"+treename)

# To help deal with potentially large files, we will process the data in 'batches'
reduced_trkana=ak.Array
for batch, report in trkana.iterate(step_size="10 MB", filter_name="/de*/i", report=True, library='ak'):

    add_useful_columns(batch)
    reduced_trkana=zip_branches(batch)

# Now define some useful masks
# - for the different generations
gen_0_mask = reduced_trkana['demmcsim.trkrel._rem']==0
gen_min1_mask = reduced_trkana['demmcsim.trkrel._rem']==1
gen_min2_mask = reduced_trkana['demmcsim.trkrel._rem']==2
gen_min3_mask = reduced_trkana['demmcsim.trkrel._rem']==3
gen_min4_mask = reduced_trkana['demmcsim.trkrel._rem']==4
# - for different particle creation processes
process = MCDataProducts.ProcessCode()
proc_ce_mask = reduced_trkana['demmcsim.gen']==process.mu2eCeMinusEndpoint
proc_pot_mask = reduced_trkana['demmcsim.gen']==process.mu2ePrimary
# - for different particle types
pdg_mu_mask = reduced_trkana['demmcsim.pdg']==13
pdg_pi_mask = reduced_trkana['demmcsim.pdg']==-211

# Now get the data we want to plot (momentum)
# - we will show that everything at gen=0 is a Ce
gen_0_mom=ak.flatten(reduced_trkana['demmcsim.mom'][(gen_0_mask)]).to_numpy()
gen_0_ce_mom=ak.flatten(batch['demmcsim.mom'][(gen_0_mask) & (proc_ce_mask)]).to_numpy()
# - we will show that everything at gen=1 is a muon
gen_min1_mom=ak.flatten(reduced_trkana['demmcsim.mom'][(gen_min1_mask)]).to_numpy()
gen_min1_mu_mom=ak.flatten(reduced_trkana['demmcsim.mom'][(gen_min1_mask) & (pdg_mu_mask)]).to_numpy()
# - we will show that everything at gen=2 is a pion
gen_min2_mom=ak.flatten(reduced_trkana['demmcsim.mom'][(gen_min2_mask)]).to_numpy()
gen_min2_pi_mom=ak.flatten(reduced_trkana['demmcsim.mom'][(gen_min2_mask) & (pdg_pi_mask)]).to_numpy()
# - we will show that *not* everything at gen=3 is a POT
gen_min3_mom=ak.flatten(reduced_trkana['demmcsim.mom'][(gen_min3_mask)]).to_numpy()
gen_min3_pot_mom=ak.flatten(reduced_trkana['demmcsim.mom'][(gen_min3_mask) & (proc_pot_mask)]).to_numpy()
# - likewise, we will show that *not* everything at gen=4 is a POT
gen_min4_mom=ak.flatten(reduced_trkana['demmcsim.mom'][(gen_min4_mask)]).to_numpy()
gen_min4_pot_mom=ak.flatten(reduced_trkana['demmcsim.mom'][(gen_min4_mask) & (proc_pot_mask)]).to_numpy()
# - finally, we will show all the POTs regardless of generation
gen_all_pot_mom=ak.flatten(reduced_trkana['demmcsim.mom'][(proc_pot_mask)]).to_numpy()

n_mom_bins=100
fig, axs = plt.subplots(3, 2, figsize=(16,9))
bins, counts, patches = axs.ravel()[0].hist(gen_0_mom, bins=n_mom_bins, range=(100,110), log=False, histtype='step', label='generation=0 (count = {})'.format(len(gen_0_mom)))
bins, counts, patches = axs.ravel()[0].hist(gen_0_ce_mom, bins=n_mom_bins, range=(100,110), log=False, histtype='stepfilled', label='generation=0 and proc=mu2eCeMinusEndpoint (count = {})'.format(len(gen_0_ce_mom)))

bins, counts, patches = axs.ravel()[1].hist(gen_min1_mom, bins=n_mom_bins, range=(0,100), log=False, histtype='step', label='generation=1 (count = {})'.format(len(gen_min1_mom)))
bins, counts, patches = axs.ravel()[1].hist(gen_min1_mu_mom, bins=n_mom_bins, range=(0,100), log=False, histtype='stepfilled', label='generation=1 and pdg==mu- (count = {})'.format(len(gen_min1_mu_mom)))

bins, counts, patches = axs.ravel()[2].hist(gen_min2_mom, bins=n_mom_bins, range=(0,200), log=False, histtype='step', label='generation=2 (count = {})'.format(len(gen_min2_mom)))
bins, counts, patches = axs.ravel()[2].hist(gen_min2_pi_mom, bins=n_mom_bins, range=(0,200), log=False, histtype='stepfilled', label='generation=2 and pdg==pi- (count = {})'.format(len(gen_min2_pi_mom)))

bins, counts, patches = axs.ravel()[3].hist(gen_min3_mom, bins=n_mom_bins, range=(0, 9000), log=False, histtype='step', label='generation=3 (count = {})'.format(len(gen_min3_mom)))
bins, counts, patches = axs.ravel()[3].hist(gen_min3_pot_mom, bins=n_mom_bins, range=(0, 9000), log=False, histtype='stepfilled', label='generation=3 and proc=POT (count = {})'.format(len(gen_min3_pot_mom)))

bins, counts, patches = axs.ravel()[4].hist(gen_min4_mom, bins=n_mom_bins, range=(0, 9000), log=False, histtype='step', label='generation=4 (count = {})'.format(len(gen_min4_mom)))
bins, counts, patches = axs.ravel()[4].hist(gen_min4_pot_mom, bins=n_mom_bins, range=(0, 9000), log=False, histtype='stepfilled', label='generation=4 and proc=POT (count = {})'.format(len(gen_min4_pot_mom)))

bins, counts, patches = axs.ravel()[5].hist(gen_all_pot_mom, bins=n_mom_bins, range=(0, 9000), log=False, histtype='stepfilled', label='all generations, proc=POT (count = {})'.format(len(gen_all_pot_mom)))
for axi in axs.ravel():
    axi.legend()
    axi.margins(x=0)
    axi.grid(True)
    axi.set_xlabel("MC Sim Particle Momentum [MeV/c]")
    axi.set_ylabel("Number of SimParticles")
fig.tight_layout()
plt.show()
