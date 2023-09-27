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

The TrkAna tree contains the results from the KinKal track fit. This is a piecewise fit which iterates through a trajectory and accounts for material and megntic field effects. Therefore, there is no value for e.g. the momentum of the track as a whole -- we can only ask what the momentum is at a given location.

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

From the ROOT command line, after you have opened the TrkAna ROOT file and ```cd```'d into the TrkAnaNeg directory.

```
trkana->Print("demfit.*")
```

, you can do:

```
trkana->Draw("demfit.mom.R()>>hist(100,100,110)", "", "HIST E")
```

to draw a histogram (100 bins between 100 MeV/c and 110 MeV/c) of the reconstructed track momentum at all the intersections (entrance, middle, and exit of the tracker). You might notice that the peak is rather broad.

Note that the ```R()``` function is a member of the ```XYZVectorF``` that we use. 

To see just the track momentum at one of the intersections, we need to apply a cut using the second argument to the ```Draw()``` function:

```
trkana->Draw("demfit.mom.R()>>hist(100,100,110)", "demfit.sid==0", "HIST E")
```

where ```sid``` is the surface id of the intersection we want to plot (```sid=0``` is the entrance to the tracker).

## Python

A bit of house-keeping. If you read through the ROOT example, you will have seen that the momentum can be easily obtained with ```demfit.mom.R()```. It is not currently possible to call the ```R()``` function (or an equivalent) in python (we are looking into [vector](https://github.com/scikit-hep/vector) as a possible tool). For the time being, we recommend defining a utility function to do these sort of calculations:

```
def add_useful_branches(batch):
    batch['demfit.mom'] = (batch['demfit.mom.fCoordinates.fX']**2 + batch['demfit.mom.fCoordinates.fY']**2 + batch['demfit.mom.fCoordinates.fZ']**2)**0.5
```



## Additional Exercises

Here are some additional exercises you might want to try:

* plot the track momentum at the middle and exit of the tracker
* plot the difference in track momentum between the entrance and the exit of the tracker

Last Page: [Plotting Global Track Information](n-hits.md)

Next Page: [Plotting MC Truth Information of the Track](mom-res.md)
