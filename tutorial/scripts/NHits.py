import uproot # for reading in ROOT files
import matplotlib.pyplot as plt # for making plots

filename="nts.brownd.CeEndpointMix1BBSignal.MDC2020z_TKAv04.tka"
treename="TrkAnaNeg/trkana"

# Open the ROOT file and be read yto read in the trkana tree
trkana = uproot.open(filename+":"+treename)

# Read in just the evtinfo id branches, and the demfit.mom branches
branches = trkana.arrays(filter_name=["/dem[.]*/"])

fig, ax = plt.subplots(1,1)

n_bins=100
xmin=0
xmax=100

counts, edges, patches = ax.hist(branches['dem.nhits'], bins=n_bins, range=(xmin,xmax), label='n hits', histtype='step')
counts, edges, patches = ax.hist(branches['dem.nactive'], bins=n_bins, range=(xmin,xmax), label='n active', histtype='step')

ax.legend()
ax.set_xlabel('Number of Hits')
ax.set_ylabel('Number of Tracks')
ax.grid(True)
plt.show()
