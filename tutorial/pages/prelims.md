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

Each entry or row in TrkAna corresponds to a single "candidate" track. Candidate tracks are the type of track that is the focus of the analysis. For example, in a muon-to-electron search analysis, the candidate tracks are downstream e-minus.

The columns of the ROOT TTree include fit information about the candidate track, as well as fit information for any "supplemental" tracks in the same event. Supplemental tracks are other track types that are needed in the analysis. For example, in a muon-to-electron search analysis, you will need to know if there were any upstream electron tracks (to veto reflected cosmic rays) or downstream muon tracks (in case a muon is a better fit), and so the supplementak tal tracks are upstream e-minus and downstream mu-minus.

## Simulation Samples

In this tutorial, we will be using the TrkAna dataset ```nts.mu2e.CeEndpointMix1BBSignal.MDC2020z_best_v1_1.tka```. The naming of the dataset is given by the [file naming convention](https://mu2ewiki.fnal.gov/wiki/FileNames). To break it down:

* ```nts```: ntuple containing simulation data
* ```CeEndpointMix1BBSignal```: description of what the dataset contains
    * ```CeEndpoint```: simulated conversion electrons
    * ```Mix```: background hits from pile-up was mixed in with the conversion electron hits
    * ```1BB```: the number of background hits was determined assuming one booster batch running
    * ```Signal```: only contains tracks that pass the signal trigger
* ```MDC2020z_best_v1_1```:
    * ```MDC2020z```: the SimJob [Musing](https://mu2ewiki.fnal.gov/wiki/Muse#Musings_.28published_muse_builds.29) that was used
    * ```best```: using the "best" alignment uncertainties we can expect
    * ```v1_1```: the conditions database version used
* ```tka```: the file type. Note that this is just a ROOT file

More details on the MDC2020 campaign and generated datasets can be found [here](https://mu2ewiki.fnal.gov/wiki/MDC2020)

Last Page: [Main Page](../README.md)

Next Page: [Logging In and Setting Up](setup.md)
