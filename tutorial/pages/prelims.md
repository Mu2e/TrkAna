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

Each entry or row in TrkAna corresponds to a single Mu2e event, and every column contains data from the event. For example, the ```dem*``` columns contain information about downtream e-minus tracks.

## Simulation Samples

In this tutorial, we will be using the TrkAna dataset ```nts.mu2e.CeEndpointMix1BBSignal.Tutorial_2024_03.tka```. The naming of the dataset is given by the [file naming convention](https://mu2ewiki.fnal.gov/wiki/FileNames). To break it down:

* ```nts```: ntuple containing simulation data
* ```CeEndpointMix1BBSignal```: description of what the dataset contains
    * ```CeEndpoint```: simulated conversion electrons
    * ```Mix```: background hits from pile-up was mixed in with the conversion electron hits
    * ```1BB```: the number of background hits was determined assuming one booster batch running
    * ```Signal```: only contains tracks that pass the signal trigger
* ```Tutorial_2024_03```: the configuration
* ```tka```: the file type. Note that this is just a ROOT file


More details on the MDC2020 campaign and generated datasets can be found [here](https://mu2ewiki.fnal.gov/wiki/MDC2020)

Last Page: [Main Page](../README.md)

Next Page: [Logging In and Setting Up](setup.md)
