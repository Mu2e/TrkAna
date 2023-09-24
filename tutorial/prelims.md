# Preliminary Information

## Objectives

On this page, you will learn about:

* the general structure of the TrkAna tree, and
* the simulation samples that we will use in the tutorial.

You will also learn how to:

* log in to the mu2egpvm machines and set up your session for the tutorials

## TrkAna Tree Structure

TrkAna is a ROOT TTree with one "candidate" track per row. A candidate track is the type of the track that is the being analyzed (e.g. downstream e-minus).

The columns of the ROOT TTree include fit information about the candidate track, as well as any "supplemental" tracks that the analysis needs. For example, in the standard TrkAna trees upstream e-minus and downstream mu-minus are supplemental tracks since a muon-to-electron conversion search will need to veto on upstream tracks, and ensure that the reconstructed particle is an electron and not a muon.


## Simulation Samples

We will be looking at the datasets ```mcs.brownd.CeEndpointMix1BBSignal.MDC2020z.art```. This file contains the output of the reconstruction for a simulation of conversion electron events (```CeEndpoint```) with background hits assuming one booster batch (```1BB```) that pass the signal trigger (```Signal```). The reconstruction pass was done using the SimJob Musing MDC2020z. More details on the MDC2020 campaign and generated datasets can be found [here](https://mu2ewiki.fnal.gov/wiki/MDC2020)

<div style="text-align: right"> Next Exercise: [Logging In and Setting Up](setup.md) </div>
