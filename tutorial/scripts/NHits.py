import sys
import uproot # for reading in ROOT files
import matplotlib.pyplot as plt # for making plots
import numpy as np

filename=sys.argv[1]
treename="TrkAnaNeg/trkana"

dem_nhits=[]
dem_nactive=[]

for batch, report in uproot.iterate(files=filename+":"+treename, filter_name=["/dem[.]*/"], step_size="10 MB", report=True):
    print(report)
    dem_nhits = np.append(dem_nhits, batch['dem.nhits'])
    dem_nactive = np.append(dem_nactive, batch['dem.nactive'])


fig, ax = plt.subplots(1,1)
ax.hist(dem_nhits, bins=100, range=(0,100), label='total number of hits', histtype='step')
ax.hist(dem_nactive, bins=100, range=(0,100), label='total number of used hits', histtype='step')

ax.legend()
ax.set_xlabel('Number of Hits')
ax.set_ylabel('Number of Tracks')
ax.grid(True)
plt.show()
