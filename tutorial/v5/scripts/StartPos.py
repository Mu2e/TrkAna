import sys
import uproot # for reading in ROOT files
import matplotlib.pyplot as plt # for making plots
import numpy as np
import awkward as ak

filename=sys.argv[1]
treename="TrkAnaNeg/trkana"

start_pos_x=[]
start_pos_y=[]
for batch, report in uproot.iterate(files=filename+":"+treename, filter_name=["/demmcsim[.]*/"], step_size="10 MB", report=True):
    print(report)

    pri_mask = (batch['demmcsim.prirel._rem']==0)

    start_pos_x = np.append(start_pos_x, ak.flatten(batch['demmcsim.pos.fCoordinates.fX'][(pri_mask)]))
    start_pos_y = np.append(start_pos_y, ak.flatten(batch['demmcsim.pos.fCoordinates.fY'][(pri_mask)]))


fig, ax = plt.subplots(1,1)

ax.hist2d(start_pos_x.to_numpy(), start_pos_y.to_numpy(), bins=200, range=[[-100,100],[-100,100]], cmin=0.1)

ax.set_xlabel('X Position (detector coords) [mm]')
ax.set_ylabel('Y Position (detector coords) [mm]')
ax.grid(True)
ax.margins(0)
plt.show()
