# Opening and Inspecting a TrkAna ROOT file

## Objectives

In this exercise, you will learn:

* how to open a TrkAna ROOT file, 
* get a list of branches in the TrkAna tree, and
* how to scan through a few events.

## Contents

* [Common Introduction](#Common-Introduction)
* [ROOT](#ROOT)
* [Python](#Python)
* [Additional Exercises](#Additional-Exercises)

## Common Introduction

TrkAna trees are contained in TrkAna ROOT files. These have the file type ```.tka``` but they are just ROOT files and so can be opened and inspected in either ROOT, or python using uproot.

In the standard TrkAna ROOT files we have two top-level directories:

* ```TrkAna```, and
* ```genCountLogger```.

The ```TrkAna``` directory contains the ```trkana``` tree. 

The ```genCountLogger``` folder contains a histogram that holds the total number of simulated events. This is necessary to normalize simulated data appropriately. It will be used in a later exercise.

In this exercise, we will open just a single TrkAna file so select one from the filelist we generated in the [last exercise](setup.md#Getting-the-List-of-TrkAna-Files).

## ROOT 

This exercise is run using the ROOT command line.

In our terminal, we can open the TrkAna ROOT file like so:

```
root -l /pnfs/mu2e/..../nts.mu2e.CeEndpointMix...MDC2020z1....tka
```

Doing a ```.ls``` will print the top-level directories:

```
root [1] .ls
TFile**         nts.mu2e.CeEndpointMix1BBSignal.MDC2020z1_best_v1_1_std_v05_00_00rc.tka
 TFile*         nts.mu2e.CeEndpointMix1BBSignal.MDC2020z1_best_v1_1_std_v05_00_00rc.tka
  KEY: TDirectoryFile   TrkAna;1     TrkAna (TrkAnaTreeMaker) folder
  KEY: TDirectoryFile   genCountLogger;1        genCountLogger (GenEventCountReader) folder
```

where we see the three directories listed earlier.

Now ```cd()``` into the ```TrkAna()``` folder and ```.ls``` the directory to see the trkana tree:

```
root [2] TrkAna->cd()
(bool) true
root [3] .ls
TDirectoryFile*         TrkAna       TrkAna (TrkAnaTreeMaker) folder
 KEY: TTree     trkana;6        track analysis [current cycle]
 KEY: TTree     trkana;5        track analysis [backup cycle]
```

Now we can ```Print()``` to see the branches of the tree:

```
root [4] trkana->Print()
(...snip...)
```

There are a lot of branches... These are documented [elsewhere](https://docs.google.com/spreadsheets/d/1IMZVgj74vxGTWqAFRtFEEcYChujJyc38VcopZh52jhc/edit) but we will go through the important ones in later tutorial exercises.

We can ```Scan()``` through the tree to see information for each event. Here we pick out the run id, subrun id, and event id of the event; and also the number of downstream e-minus tracks in the event (```tcnt.ndem``` = track count):

```
root [5] trkana->Scan("evtinfo.runid:evtinfo.subrunid:evtinfo.eventid:tcnt.ndem")
***********************************************************************
*    Row   * Instance * evtinfo.r * evtinfo.s * evtinfo.e * tcnt.ndem *
***********************************************************************
*        0 *        0 *      1210 *         0 *         1 *         1 *
*        0 *        1 *      1210 *         0 *         1 *         1 *
*        0 *        2 *      1210 *         0 *         1 *         1 *
*        1 *        0 *      1210 *         0 *         4 *         1 *
*        1 *        1 *      1210 *         0 *         4 *         1 *
*        1 *        2 *      1210 *         0 *         4 *         1 *
*        2 *        0 *      1210 *         0 *         7 *         1 *
*        2 *        1 *      1210 *         0 *         7 *         1 *
*        2 *        2 *      1210 *         0 *         7 *         1 *
```


## Python

The python exercise can be run either in the python command line or with a python notebook.

To open and inspect the TrkAna ROOT file with python, we will use [uproot](https://uproot.readthedocs.io/en/latest/index.html), which we need to import:

```
import uproot
```

Next, we open up the file and look at its contents like this:

```
file = uproot.open("/pnfs/mu2e/..../nts.mu2e.CeEndpointMix...MDC2020z1....tka")
file.keys()
```

which will produce the output:

```
['TrkAna;1', 'TrkAna/trkana;6', 'TrkAna/trkana;5', 'genCountLogger;1', 'genCountLogger/numEvents;1', 'genCountLogger/numSubRuns;1']
```

where we see that uproot has descended into each of the three top-level directories listed earlier to get the contents of each.

The TrkAna tree can be accessed and the branches inspected by doing:

```
trkana = file["TrkAna"]["trkana"]
trkana.keys()
```

which will produce a lot of output since there are a lot of branches. These are documented [elsewhere](https://docs.google.com/spreadsheets/d/1IMZVgj74vxGTWqAFRtFEEcYChujJyc38VcopZh52jhc/edit) but we will go through the important ones in later tutorial exercises.

Note that getting the TrkAna tree can be done in a single step like this:

```
trkana = uproot.open("/pnfs/mu2e/..../nts.mu2e.CeEndpointMix...MDC2020z1....tka:TrkAna/trkana")
```

With ```trkana``` defined we can now get its contents using the ```arrays()``` function. This function reads the data into an [awkward array](https://awkward-array.org/doc/main/). A brief note on this: in HEP we often have different numbers of physics objects in each event, and so they will not fit efficiently into fixed-length arrays. For example, if we want to store the straw hits in the tracker, there will be a different number in each event. Therefore we need to use "awkward" or "ragged" arrays, which requires the use of the awkward array package. This is the default library used by uproot to read branches.

The first entry in the TTree can be seen with:

```
trkana.arrays()[0]
```

and you can also use python slicing to look at the first ```N``` events:

```
trkana.arrays()[:N]
```

or the events between ```N``` and ```M```:

```
trkana.arrays()[N:M]
```

You may notice that this is slow: one important difference between python and ROOT is that python will automatically ready the whole tree into memory. In later exercises, we will find ways around this. For the time being, we will use the ```filter_name``` argument to the ```arrays()``` function to reduce the amount of data we read in. For example:

```
branches = trkana.arrays(filter_name=["/evtinfo.*id/", "/tcnt.*/"])
print(branches.fields)
```

will read in the just the ```evtinfo.*``` and ```tcnt.*``` branches.

Then you can inspect these branches with ```branches[N:M]```


## Additional Exercises
Try some of the following additional exercises:

* get the number of downstream e-plus tracks

Last Page: [Logging In and Setting Up](setup.md)

Next Page: [Plotting Global Track Information](n-hits.md)
