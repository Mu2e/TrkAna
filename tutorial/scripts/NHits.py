import uproot # for reading in ROOT files
import matplotlib.pyplot as plt # for making plots

filename="nts.brownd.CeEndpointMix1BBSignal.MDC2020z_TKAv04.tka"
treename="TrkAnaNeg/trkana"

# Open the ROOT file and be read yto read in the trkana tree
trkana = uproot.open(filename+":"+treename)

# Read in just the dem. branch
branches = trkana.arrays(filter_name=["/dem[.]*/"])

fig, ax = plt.subplots(1,1)

counts, edges, patches = ax.hist(branches['dem.nhits'], bins=100, range=(0,100), label='total number of hits', histtype='step')
counts, edges, patches = ax.hist(branches['dem.nactive'], bins=100, range=(0,100), label='total number of used hits', histtype='step')

ax.legend()
ax.set_xlabel('Number of Hits')
ax.set_ylabel('Number of Tracks')
ax.grid(True)
plt.show()
