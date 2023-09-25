# Preliminary Information

## Objectives

On this page, you will learn about:

* the general structure of the TrkAna tree, and
* the simulation samples that we will use in the tutorial.

## Contents

* [TrkAna Tree Structure](#TrkAna-Tree-Structure)
* [Simulation Samples](#Simulation-Samples)

## TrkAna Tree Structure

TrkAna is a ROOT TTree that contains the results of the track reconstruction. It is designed for simple data exploration as well as to be used as input into to both ROOT- and python-based analyis frameworks. 

Each entry or row in TrkAna corresponds to a single "candidate" track. Candidate tracks are of a given type (e.g. downstream e-minus) the type of track that is the being analyzed (e.g. downstream e-minus).

The columns of the ROOT TTree include fit information about the candidate track, as well as any "supplemental" tracks in the same event that the analysis needs. For example, in the standard TrkAna trees upstream e-minus and downstream mu-minus are supplemental tracks since a muon-to-electron conversion search will need to veto on upstream tracks, and ensure that the reconstructed particle is an electron and not a muon.

## Simulation Samples

In this tutorial, we will be looking at the dataset ```mcs.brownd.CeEndpointMix1BBSignal.MDC2020z.art```. The naming of the dataset is given by the [file naming convention](https://mu2ewiki.fnal.gov/wiki/FileNames). To break it down:

* ```mcs```: reconstructed data from simulation
* ```CeEndpointMix1BBSignal```: description of what the dataset contains
    * ```CeEndpoint```: simulated conversion electrons
    * ```Mix```: background hits from pile-up was mixed in with the conversion electron hits
    * ```1BB```: the number of background hits was determined assuming one booster batch running
    * ```Signal```: only contains tracks that pass the signal trigger
* ```MDC2020z```: reconstruction pass was done using the SimJob Musing MDC2020z.

More details on the MDC2020 campaign and generated datasets can be found [here](https://mu2ewiki.fnal.gov/wiki/MDC2020)

Last Page: [Main Page](README.md)

Next Page: [Logging In and Setting Up](setup.md)
