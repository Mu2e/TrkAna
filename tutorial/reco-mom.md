# Plotting the Reconstructed Track Momentum of Conversion Electrons

## Objectives

In this exercise, you will learn:

* about the ```fit``` branches and how they are, and
* how to plot the reconstructed momentum of tracks.

## Contents

* [Common Introduction](#Common-Introduction)
* [ROOT](#ROOT)
* [Python](#Python)

## Common Introduction

The TrkAna tree contains the results from the KinKal track fit. This is a piecewise fit and so there is no value for the momentum of the whole track -- we can only say what the momentum is at a given location. In Offline, we define surfaces and can ask "what were the parameters of the track when it intersected this surface?"

In TrkAna, we can store the information from any number of surfaces. We currently pick three: the entrance, middle, and exit of the tracker. In order to allow for future expansion, we store the track information from all these locations as a vector in a single branch: ```demfit```.

To differentiate between these we will use the [SurfaceId](https://github.com/Mu2e/Offline/blob/v10_23_01/KinKalGeom/inc/SurfaceId.hh) of each surface:

* surface id = 0: entrance to tracker
* surface id = 1: middle of tracker
* surface id = 2: exit of tracker

## ROOT



## Python

A bit of house-keeping. If you read through the ROOT example, you will have seen that the magnitude of the momentum can be easily obtained with ```demfit.mom.R()```. It is not currently possible to call the ```R()``` function in python so we recommend defining a utility function to do this calculation:

```
def add_useful_branches(batch):
    batch['demfit.mom'] = (batch['demfit.mom.fCoordinates.fX']**2 + batch['demfit.mom.fCoordinates.fY']**2 + batch['demfit.mom.fCoordinates.fZ']**2)**0.5
```

Last Page: [Opening and Inspecting a TrkAna ROOT file](opening.md)

Next Page: [Applying Cuts](cuts.md)
