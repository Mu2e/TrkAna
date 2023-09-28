# Plotting the Reconstructed Track Momentum of Conversion Electrons

## Objectives

In this exercise, you will learn:

* about the ```demfit``` and ```demlh``` branches, 
* how to plot the reconstructed momentum of tracks, and
* apply a cut.

## Contents

* [Common Introduction](#Common-Introduction)
    * [Track Fit Parameters](#Track-Fit-Parameters)
    * [Track Fit Intersection](#Track-Fit-Intersection)
* [ROOT](#ROOT)
* [Python](#Python)
* [Additional Exercises](#Additional-Exercises)

## Common Introduction

The TrkAna tree contains the results from the KinKal track fit. This is a piecewise fit which iterates through a trajectory and accounts for material and megntic field effects.

### Track Fit Intersections

Since KinKal is a piecewise fit, there is no value for the momentum of the whole track -- we can only  In Offline, we define surfaces and can ask "what were the parameters of the track when it intersected this surface?"

In TrkAna, we can store the information from any number of surfaces. We currently pick three: the entrance, middle, and exit of the tracker. In order to allow for future expansion, we store the track information from all these locations as a vector in a single branch: ```demfit```.

To differentiate between these we will use the [SurfaceId](https://github.com/Mu2e/Offline/blob/v10_23_01/KinKalGeom/inc/SurfaceId.hh) of each surface:

* surface id = 0: entrance to tracker
* surface id = 1: middle of tracker
* surface id = 2: exit of tracker

We store the position and momentum as the three individual x, y, and z components. 

### Track Fit Parameters

KinKal supports three different track parameterizations:

* LoopHelix: looping tracks like conversion electrons in Mu2e
* KinematicLine: straight-line tracks like cosmic rays
* CentralHelix: curved tracks like cosmic rays with magnetic field on

Depending on the type of track we are fitting, TrkAna will put the fit parameters (and their uncertainties) in the ```demlh```, ```demkl```, or ```demch```. 


## ROOT

In ROOT, we can open the ROOT file, get the TrkAna tree, and create a TCanvas as usual:

```
TFile* file = new TFile("nts.brownd.CeEndpointMix1BBSignal.MDC2020z_TKAv04.tka", "READ");
TTree* trkana = (TTree*) file->Get("TrkAnaNeg/trkana");

TCanvas* c1 = new TCanvas("c1", "c1");
c1->SetGridx(true);
c1->SetGridy(true);
```

We want to plot the momentum of the tracks. If you ```Print()``` the ```demfit``` branch, you will notice that the momentum is split into its three components:

```
*............................................................................*
*Br    1 :demfit.mom.fCoordinates.fX : Float_t fX[demfit_]                   *
*Entries :   130524 : Total  Size=    2091152 bytes  File Size  =    1617083 *
*Baskets :       21 : Basket Size=     586240 bytes  Compression=   1.29     *
*............................................................................*
*Br    2 :demfit.mom.fCoordinates.fY : Float_t fY[demfit_]                   *
*Entries :   130524 : Total  Size=    2091152 bytes  File Size  =    1616994 *
*Baskets :       21 : Basket Size=     586240 bytes  Compression=   1.29     *
*............................................................................*
*Br    3 :demfit.mom.fCoordinates.fZ : Float_t fZ[demfit_]                   *
*Entries :   130524 : Total  Size=    2091152 bytes  File Size  =    1513081 *
*Baskets :       21 : Basket Size=     586240 bytes  Compression=   1.38     *
*............................................................................*
```

We want to plot the magnitude of the momentum vector. We could calculate it ourselves from the components but in ROOT, we can use member functions of [XYZVectorF](https://root.cern.ch/doc/v628/namespaceROOT_1_1Math.html#a767e8c52a85dc9538fe00603961eab98). We will use ```R()``` function:

```
trkana->Draw("demfit.mom.R()>>hist(100,100,110)", "", "HIST");
```

You may notice that the peak is rather broad... That's because we are plotting the reconstructed track momentum at all the intersections - the entrance, middle, and exit of the tracker. 

To see just the track momentum at one of the intersections, we need to apply a cut using the second argument to the ```Draw()``` function:

```
trkana->Draw("demfit.mom.R()>>hist(100,100,110)", "demfit.sid==0", "HIST")
```

where ```sid``` is the surface id of the intersection we want to plot (```sid=0``` is the entrance to the tracker).

We might also want to make a cut on some other track parameter. For example, in the Mu2e muon-to-electron conversion search we will apply a time cut to the tracks. Again, like for momentum, there is no "time" for the whole track and we have the time at each intersection. The time is part of the parameterization and is stored in the ```demlh``` branch:

```
trkana->Draw("demfit.mom.R()>>hist2", "demfit.sid==0 && demlh.t0>=700" "HIST SAME");
```

## Python

In python, we will need to import awkward directly 

```
import uproot
import matplotlib.pyplot as plt
import awkward as ak

trkana = uproot.open("nts.brownd.CeEndpointMix1BBSignal.MDC2020z_TKAv04.tka:TrkAnaNeg/trkana")

fig, ax = plt.subplots(1,1)
```

Now let's read in just the ```demfit``` and ```demlh``` branches:

```
branches = trkana.arrays(filter_name=["/demfit[.]*/", "/demlh[.]*/"])
```

We want to plot the momentum

If you look at the ```branches.fields```, you will see that we store the momentum in its x, y, and z components:

```
print(branches.fields)
['demfit.mom.fCoordinates.fX', 'demfit.mom.fCoordinates.fY', 'demfit.mom.fCoordinates.fZ', 'demfit.pos.fCoordinates.fX', 'demfit.pos.fCoordinates.fY', 'demfit.pos.fCoordinates.fZ', 'demfit.time', 'demfit.momerr', 'demfit.inbounds', 'demfit.gap', 'demfit.early', 'demfit.late', 'demfit.sid', 'demfit.sindex']
```

so we will have to calculate the magnitude of the momentum ourselves. (If you read through the ROOT example, you will have seen that the momentum can be easily obtained with ```demfit.mom.R()```. It is not currently possible to call the ```R()``` function (or an equivalent) in python but we are looking into [vector](https://github.com/scikit-hep/vector) as a possible tool). 

Anyway, it is easy to add a column in python:

```
batch['demfit.mom'] = (batch['demfit.mom.fCoordinates.fX']**2 + batch['demfit.mom.fCoordinates.fY']**2 + batch['demfit.mom.fCoordinates.fZ']**2)**0.5
```

If you try to plot this like we did before:

```
ax.hist(branches['demfit.mom'], bins=100, range=(100,110), label='all tracks', histtype='step')
```

you will get an error. That's because the ```demfit``` branch is an array, and the function doesn't like that. So we need to ```flatten``` it down to one dimension:

```
ax.hist(ak.flatten(branches['demfit.mom'], bins=100, range=(100,110), label='all tracks', histtype='step')
```

Now you may notice that the peak is rather broad... That's because the ```demfit``` branch contains the fit information at the entrance, middle, and exit of the tracker.

To plot just the momentum at the tracker entrance, we need to make a "mask array", which is an array of the same shape and dimensionality as our data but containing either ```True``` or ```False```:

```
trk_ent_mask = (branches['demfit.sid']==0)
```

To see what I mean about the dimensionality and shape you can ```print``` them:

```
print(branches['demfit.sid'])
print(trk_ent_mask)
```

Now we need to use this mask when plotting:

```
ax.hist(ak.flatten(branches['demfit.mom'][(trk_ent_mask)], bins=100, range=(100,110), label='all tracks', histtype='step')

ax.set_xlabel('Reconstructed Momentum at Tracker Entrance [MeV/c]')
ax.set_ylabel('Number of Tracks')
ax.legend()
ax.grid(True)
plt.show()
```

We might also want to make a cut on some other track parameter. For example, in the Mu2e muon-to-electron conversion search we will apply a time cut to the tracks. Again, like for momentum, there is no "time" for the whole track and we have the time at each intersection. The time is part of the parameterization and is stored in the ```demlh``` branch. Let's make a mask for it:

```
time_cut_mask = (branches['demlh.t0']>=700)
```

and to use it when plotting we need to use the bitwise ```&``` operator.

```
ax.hist(ak.flatten(branches['demfit.mom'][(trk_ent_mask) & (time_cut_mask)], bins=100, range=(100,110), label='all tracks', histtype='step')
```


## Additional Exercises

Here are some additional exercises you might want to try:

* plot the track momentum at the middle and exit of the tracker
* plot the difference in track momentum between the entrance and the exit of the tracker

Last Page: [Plotting Global Track Information](n-hits.md)

Next Page: [Plotting MC Truth Information of the Track](mom-res.md)
