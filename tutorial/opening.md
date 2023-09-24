# Opening and Inspecting a TrkAna ROOT file

In this exercise, we will open the TrkAna ROOT file and inspect the TrkAna TTree and its branches.

## Introduction

We will use ROOT to look in the TrkAna ROOT file to see what it contains.

Open the TrkAna ROOT file on the command line like so:

```
root -l nts.brownd.CeEndpointMix1BBSignal.MDC2020z_TKAv4.tka
```

Doing a ```.ls``` will print the top-level directories:

```
root [1] .ls
TFile**         nts.brownd.CeEndpointMix1BBSignal.MDC2020z_TKAv04.tka
 TFile*         nts.brownd.CeEndpointMix1BBSignal.MDC2020z_TKAv04.tka
  KEY: TDirectoryFile   TrkAnaNeg;1     TrkAnaNeg (TrkAnaTreeMaker) folder
  KEY: TDirectoryFile   TrkAnaPos;1     TrkAnaPos (TrkAnaTreeMaker) folder
  KEY: TDirectoryFile   genCountLogger;1        genCountLogger (GenEventCountReader) folder
```

We see that there are two TrkAna directories: ```TrkAnaNeg``` and ```TrkAnaPos```. These are two separate TrkAna trees where the candidate tracks are downstream e-minus and downstream mu-plus, respectively. (And the supplemental tracks are upstream e-minus + downstream mu-minus, and upstream e-plus + downstream mu-plus, respectively).

The ```genCountLogger``` folder contains a histogram that holds the total number of simulated events. This is necessary to normalize simulated data appropriately. It will be used in a later exercise.


## ROOT


## Python
