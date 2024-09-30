import sys
import uproot # for reading in ROOT files
import matplotlib.pyplot as plt # for making plots
import numpy as np
import awkward as ak

filename=sys.argv[1]
treename="TrkAna/trkana"

dem_nhits=[]
dem_nactive=[]
dem_nhits_ndem2=[]
dem_nactive_ndem2=[]

for batch, report in uproot.iterate(files=filename+":"+treename, filter_name=["/tcnt/", "/dem/"], step_size="10 MB", report=True):
    print(report)
    dem_nhits = np.append(dem_nhits, ak.flatten(batch['dem.nhits']))
    dem_nactive = np.append(dem_nactive, ak.flatten(batch['dem.nactive']))

    tcnt_ndem2_mask = batch['tcnt.ndem']==2

    dem_nhits_ndem2 = np.append(dem_nhits_ndem2, ak.flatten(batch[(tcnt_ndem2_mask)]['dem.nhits']))
    dem_nactive_ndem2 = np.append(dem_nactive_ndem2, ak.flatten(batch[(tcnt_ndem2_mask)]['dem.nactive']))

fig, axs = plt.subplots(2,1)
axs[0].hist(dem_nhits, bins=100, range=(0,100), label='total number of hits', histtype='step')
axs[0].hist(dem_nactive, bins=100, range=(0,100), label='total number of used hits', histtype='step')

axs[0].legend()
axs[0].set_xlabel('Number of Hits')
axs[0].set_ylabel('Number of Tracks')
axs[0].grid(True)

axs[1].hist(dem_nhits_ndem2, bins=100, range=(0,100), label='total number of hits', histtype='step')
axs[1].hist(dem_nactive_ndem2, bins=100, range=(0,100), label='total number of used hits', histtype='step')

axs[1].legend()
axs[1].set_xlabel('Number of Hits')
axs[1].set_ylabel('Number of Tracks')
axs[1].grid(True)
plt.show()
