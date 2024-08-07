# Plotting MC Truth Information of the Track

## Objectives

In this exercise, you will:

* follow the genealogy of the conversion electrons to plot the start positions of their parent muons, and
* learn about the ```ProcessCode```

## Contents

* [Common Introduction](#Common-Introduction)
* [ROOT](#ROOT)
* [Python](#Python)
* [Additional Exercises](#Additional-Exercises)

## Common Introduction

In the [last exercise](start-pos.md) we learned that the ```demmcsim``` branch has the information for the full genealogy of particles that created the conversion electron. We will go back one generation to plot the start position of the muons that created the conversion electron. Note that currently we only store the start position and momentum of particles. We plan to add the end position and momentum soon.

One issue you may come across is that you want to know about particles created by a specific process, regardless of where in the genealogy they were created. For this, we store the [ProcessCode](https://github.com/Mu2e/Offline/blob/v10_23_02/MCDataProducts/inc/ProcessCode.hh) of the process that created the partcle in the ```demmcsim.gen``` leaf. In this exercise, we will look at the start positions of decay-in-orbit (DIO) electrons that were reconstructed. Due to our simulation procedure, there are actually two different ```ProcessCodes``` for decay-in-orbit electrons:
* ```ProcessCode::mu2eDecayAtRest``` (166) are the DIO electrons that we generate in the stopping target. We have a specially calculated DIO energy spectrum that is more accurate than the Geant4 one.
* ```ProcessCode::DIO``` (114) are the DIO electrons that are generated by muon stops elsewhere. In this case, we use Geant4's DIO energy spectrum.


## ROOT
In ROOT, let's open the file, get the tree, and create a TCanvas as before:

```
TChain* trkana = new TChain("TrkAna/trkana");

std::ifstream input_filelist("filelists/nts.mu2e.CeEndpointMix1BBSignal.MDC2020z1_best_v1_1_std_v04_01_00.list");
if (input_filelist.is_open()) {
  std::string filename;
  while(std::getline(input_filelist,filename)) {
    trkana->Add(filename.c_str());
  }
  input_filelist.close();
}


TCanvas* c1 = new TCanvas("c1", "c1");
c1->SetGridx(true);
c1->SetGridy(true);
```

Now we can draw the X-Z starting position of the conversion electrons like this:

```
  TH2D* hist = new TH2D("hist", "", 1000,-20000,1000, 1000,-700,9000);
  trkana->Draw("demmcsim.pos.x():demmcsim.pos.z()>>hist", "demmcsim.prirel._rem==1 && demmcsim.prirel._rel==2", "COLZ");
```
where ```prirel._rel==2``` is for parent. You should see the S-bend of the transport solenoid and also the production solenoid.

We can draw the R-Z starting position of the DIO electrons not in the target like this:

```
  trkana->Draw("demmcsim.pos.rho():demmcsim.pos.z()>>h_StartPos_DIO", "demmcsim.gen==114 && demmcsim.trkrel._rem==0");
```

where ```trkrel._rem==0``` means that these are DIO electrons that we actually reconstructed, and ```gen==114``` is for the non-stopping target DIO electrons. You will see that most of the entries in the histogram are at R=300 mm. This is the inner proton absorber. If you change the ```gen``` cut to ```gen==166``` you will see that these were generated in the stopping target region.


## Python

In python, we can set up as normal:

```
import uproot
import matplotlib.pyplot as plt
import numpy as np
import awkward as ak

for batch, report in uproot.iterate(files=wildcarded_dir+":TrkAna/trkana", filter_name=["/demmcsim[.]*/"], step_size="10 MB", report=True):
    print(report)


fig, ax = plt.subplots(1,1)
```

Before the iterate loop, we will create arrays for the x, y, and z positions of the parent muons and the DIO electrons:

```
start_pos_x=[]
start_pos_y=[]
start_pos_z=[]
```

Within the iterate loop, we need a mask for the parents of the conversion electrons:

```
    parent_mask = (batch['demmcsim.prirel._rem']==1) & (batch['demmcsim.prirel._rel']==2)

    start_pos_x = np.append(start_pos_x, ak.flatten(batch['demmcsim.pos.fCoordinates.fX'][(parent_mask)]))
    start_pos_y = np.append(start_pos_y, ak.flatten(batch['demmcsim.pos.fCoordinates.fY'][(parent_mask)]))
    start_pos_z = np.append(start_pos_z, ak.flatten(batch['demmcsim.pos.fCoordinates.fZ'][(parent_mask)]))
```
where ```prirel._rel==2``` is for parent.

And then we can plot the X-Z positions like this:

```
fig, ax = plt.subplots(1,1)
ax.hist2d(start_pos_z.to_numpy(), start_pos_x.to_numpy(), bins=1000, range=[[-20000,1000],[-700,9000]], cmin=0.1)
ax.set_xlabel('Z Position (detector coords) [mm]')
ax.set_ylabel('X Position (detector coords) [mm]')
ax.grid(True)
ax.margins(0)
```
You should see the S-bend of the transport solenoid and also the production solenoid.

For plotting the positions of DIO electrons, we don't need to remember the process code numbers. Instead we can import the ```MCProducts``` class directly because it is included in our comman python environment through [PyWrap](https://mu2ewiki.fnal.gov/wiki/PyWrap). This wraps some of our classes so that they can be called in python. To do this we just import MCDataProducts and get the enum:

```
import MCDataProducts
process = MCDataProducts.ProcessCode()
```

Then our mask in the iterate loop looks like this:

```
    dio_mask = (batch['demmcsim.trkrel._rem']==0) & (batch['demmcsim.gen']==process.DIO)
```
where ```trkrel._rem==0``` means that this is the particle that was reconstructed and ```process.DIO``` is for the non-stopped target DIO electrons.

Before the iterate loop, we can make arrays to store the x,y,z positions of the DIO electrons:

```
dio_start_pos_x=[]
dio_start_pos_y=[]
dio_start_pos_z=[]
```

and then in the iterate loop, we make the cut like so:

```
    dio_start_pos_x = np.append(dio_start_pos_x, ak.flatten(batch['demmcsim.pos.fCoordinates.fX'][(dio_mask)]))
    dio_start_pos_y = np.append(dio_start_pos_y, ak.flatten(batch['demmcsim.pos.fCoordinates.fY'][(dio_mask)]))
    dio_start_pos_z = np.append(dio_start_pos_z, ak.flatten(batch['demmcsim.pos.fCoordinates.fZ'][(dio_mask)]))
```

Finally, we can draw the R-Z starting position of the DIO electrons like this:

```
fig, ax = plt.subplots(1,1)
ax.hist2d(dio_start_pos_z.to_numpy(), ((dio_start_pos_x**2+dio_start_pos_y**2)**0.5).to_numpy(), bins=100, range=[[-5500,1000],[0,500]], cmin=0.1)
ax.set_xlabel('Z Position (detector coords) [mm]')
ax.set_ylabel('Radial Position (detector coords) [mm]')
ax.grid(True)
ax.margins(0)
```

You will see that most of the entries in the histogram are at R=300 mm. This is the inner proton absorber. If you change the mask to use ```process.mu2eMuonDecayAtRest``` you will see that these were generated in the stopping target region.


## Additional Exercises
Here are some additional exercises, you might want to try:
* plot the momentum of the two types of DIO electrons


Last Page: [Plotting MC Truth Information of the Particle](start-pos.md)

Next Page: [Plotting MC Truth Information of the Particle](e-loss.md)
