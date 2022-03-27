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

# Create a figure to put our plots on
fig, ax = plt.subplots(1,1)

# Create a histogram of all the tracks
content, edges, patches = ax.hist(df["de.t0"],
                                  bins=170, 
                                  range=(0,1700), 
                                  label="all tracks",
                                  histtype='step')

# Now we want to select a subset of all the tracks and plot them on the same set of axes
# There are a few qays to do this.

#
# 1. Using df.loc[]
#
# Here we extract the rows from the original data frame that pass our selection cut.
# BUT this makes a copy of the data frame and so will not scale to large datasets
#
selected_df = df.loc[df["de.t0"]>800]
content, edges, patches = ax.hist(selected_df["de.t0"],
                                  bins=170,
                                  range=(0,1700),
                                  label="selected tracks (using df.loc[])",
                                  histtype='step')

#
# 2. Selecting while plotting
#
# To avoid making a copy, we could select tracks when plotting
# BUT If you want to plot more variables with the same selection and then edit the selection,
# you will have to edit your script in multiple places
#
content, edges, patches = ax.hist(df[df["de.t0"]>1000]["de.t0"],
                                  bins=170,
                                  range=(0,1700),
                                  label="selected tracks (while plotting)",
                                  histtype='step')

#
# 3. Adding a column of bools
#
# To avoid having to update your selection in multiple places, you can add a column of bools
# to the original data frame. This has a small memory cost (sizeof(bool) * n_rows) but allows
# for more flexibility
#
df["selected"] = df["de.t0"]>1200
content, edges, patches = ax.hist(df[df["selected"]==True]["de.t0"],
                                  bins=170,
                                  range=(0,1700),
                                  label="selected tracks (adding column of bool)",
                                  histtype='step')


ax.legend()
plt.show()
