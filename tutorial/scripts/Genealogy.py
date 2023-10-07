import sys
import uproot # for reading in ROOT files
import matplotlib.pyplot as plt # for making plots
import numpy as np
import awkward as ak
import MCDataProducts # for process codes etc.

filename=sys.argv[1]
treename="TrkAnaNeg/trkana"

start_pos_x=[]
start_pos_y=[]
start_pos_z=[]

dio_start_pos_x=[]
dio_start_pos_y=[]
dio_start_pos_z=[]

process = MCDataProducts.ProcessCode()
for batch, report in uproot.iterate(files=filename+":"+treename, filter_name=["/demmcsim[.]*/"], step_size="10 MB", report=True):
    print(report)

    parent_mask = (batch['demmcsim.prirel._rem']==1) & (batch['demmcsim.prirel._rel']==2)

    start_pos_x = np.append(start_pos_x, ak.flatten(batch['demmcsim.pos.fCoordinates.fX'][(parent_mask)]))
    start_pos_y = np.append(start_pos_y, ak.flatten(batch['demmcsim.pos.fCoordinates.fY'][(parent_mask)]))
    start_pos_z = np.append(start_pos_z, ak.flatten(batch['demmcsim.pos.fCoordinates.fZ'][(parent_mask)]))

#    dio_mask = (batch['demmcsim.trkrel._rem']==0) & (batch['demmcsim.gen']==process.DIO)
    dio_mask = (batch['demmcsim.trkrel._rem']==0) & (batch['demmcsim.gen']==process.mu2eMuonDecayAtRest)

    dio_start_pos_x = np.append(dio_start_pos_x, ak.flatten(batch['demmcsim.pos.fCoordinates.fX'][(dio_mask)]))
    dio_start_pos_y = np.append(dio_start_pos_y, ak.flatten(batch['demmcsim.pos.fCoordinates.fY'][(dio_mask)]))
    dio_start_pos_z = np.append(dio_start_pos_z, ak.flatten(batch['demmcsim.pos.fCoordinates.fZ'][(dio_mask)]))


fig, ax = plt.subplots(1,1)
ax.hist2d(start_pos_z.to_numpy(), start_pos_x.to_numpy(), bins=1000, range=[[-20000,1000],[-700,9000]], cmin=0.1)
ax.set_xlabel('Z Position (detector coords) [mm]')
ax.set_ylabel('X Position (detector coords) [mm]')
ax.grid(True)
ax.margins(0)

fig, ax = plt.subplots(1,1)
ax.hist2d(dio_start_pos_z.to_numpy(), ((dio_start_pos_x**2+dio_start_pos_y**2)**0.5).to_numpy(), bins=100, range=[[-5500,1000],[0,500]], cmin=0.1)
ax.set_xlabel('Z Position (detector coords) [mm]')
ax.set_ylabel('Radial Position (detector coords) [mm]')
ax.grid(True)
ax.margins(0)

plt.show()
