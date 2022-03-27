#
# Adapated from the example in the Mu2e Wiki here: https://mu2ewiki.fnal.gov/wiki/TrkAna#Python (Thanks, Roberto!)
#
# To run (on a mu2egpvm machine): 
# > setup mu2e
# > muse setup TrkAna
# > setup pyana
# > python TrkAna/examples/pandas-example.py
#
import pandas as pd
import uproot
import matplotlib.pyplot as plt

# Reading in the full trkana tree into a pandas dataframe gives a performance warning ("DataFrame is highly fragmented.").
from warnings import simplefilter
simplefilter(action="ignore", category=pd.errors.PerformanceWarning)

#Open the file, grab the trkana tree and show it
filename = "nts.owner.trkana-reco.version.sequencer.root"
dirname = "TrkAnaNeg"
treename = "trkana"
file = uproot.open(filename)
trkana = file[dirname][treename]

df = trkana.arrays(library='pd') # Read the full trkana tree into a Pandas dataframe


fig, ax = plt.subplots(1,1)
content, edges, patches = ax.hist(df["de.t0"],
                                  bins=170, 
                                  range=(0,1700), 
                                  label="all tracks",
                                  histtype='step')

selected_df = df.loc[df["de.t0"]>1000]
content, edges, patches = ax.hist(selected_df["de.t0"],
                                  bins=170, 
                                  range=(0,1700), 
                                  label="selected tracks",
                                  histtype='step')
ax.legend()
plt.show()
