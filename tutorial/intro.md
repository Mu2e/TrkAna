# TrkAna Tutorial

## Introduction

Welcome to the TrkAna Tutorial! These exercises are designed to be self-paced and pick-and-choose. Both ROOT- and python-based examples are shown.

## TrkAna Tree Structure

TrkAna is a ROOT TTree with one "candidate" track per row. A candidate track is the type of the track that is the being analyzed (e.g. downstream e-minus).

The columns of the ROOT TTree include fit information about the candidate track, as well as any "supplemental" tracks that the analysis needs. For example, in the standard TrkAna trees upstream e-minus and downstream mu-minus are supplemental tracks since a muon-to-electron conversion search will need to veto on upstream tracks, and ensure that the reconstructed particle is an electron and not a muon.

## General Setup

For ROOT exercises, you should log in to a mu2egpvm machine:

```
ssh -XY username@mu2egpvm0X.fnal.gov
cd to/your/working/area/
setup mu2e
muse setup TrkAna v04_00_00
```

where ```mu2egpvm0X``` is between ```mu2egpvm01``` and ```mu2egpvm06```.

For python exercises using jupyter notebooks, you should log into to a mu2egpvm machine and do some port forwarding:

```
ssh -XY -L YYYY:localhost:YYYY username@mu2egpvm0X.fnal.gov
```

where ```YYYY``` is a port number (e.g. 3000, 3001) that you will use to open a browser on your local machine.

## Simulation Samples

We will be looking at the datasets ```mcs.brownd.CeEndpointMix1BBSignal.MDC2020z.art```. This file contains the output of the reconstruction for a simulation of conversion electron events (```CeEndpoint```) with background hits assuming one booster batch (```1BB```) that pass the signal trigger (```Signal```). The reconstruction pass was done using the SimJob Musing MDC2020z. More details on the MDC2020 campaign and generated datasets can be found [here](https://mu2ewiki.fnal.gov/wiki/MDC2020)

## Exercises

Here are the list of exercises in this tutorial:

1. [Opening and Inspecting a TrkAna ROOT file](opening.md)

In this exercise we will open and inspect the TrkAna ROOT files

1. [Plotting the Reconstructed Track Momentum of Conversion Electrons](reco-mom.md)

In this exercise we will describe the ```demfit``` branches and plot the reconstructed track momentum at the entrance, middle, and exit of the tracker

<!----
Hope to get to these...

1. [Plotting the Simulated Energy Loss of Conversion Electrons](e-loss.md)

1. [Following the Genealogy of Conversion Electrons](genealogy.md)

1. [Plotting the Time Difference between a Track and CRV hit](crv.md)

1. [Plotting the Reconstructed Track Momentum of particles that weren't the conversion electron]

1. [Plotting the Simulated Energy Loss of Conversion Electrons in the Stopping Target and IPA](e-loss.md)

--->
