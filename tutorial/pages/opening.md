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

In the standard TrkAna ROOT files we have three top-level directories:

* ```TrkAnaNeg```,
* ```TrkAnaPos```, and
* ```genCountLogger```.

The two ```TrkAnaNeg``` and ```TrkAnaPos``` directories contain different TrkAna trees. ```TrkAnaNeg``` contains a TrkAna tree where the candidate tracks are downstream e-minus, and the supplemental tracks upstream e-minus, and downstream mu-minus. ```TrkAnaPos``` contains a TrkAna tree where the candidate tracks are downstream e-plus, and the supplemental tracks upstream e-plus, and downstream mu-plus.

The ```genCountLogger``` folder contains a histogram that holds the total number of simulated events. This is necessary to normalize simulated data appropriately. It will be used in a later exercise.

## ROOT 

This exercise is run using the ROOT command line.

In our terminal, we open the TrkAna ROOT file like so:

```
root -l nts.brownd.CeEndpointMix1BBSignal.MDC2020z_TKAv04.tka
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

where we see the three directories listed earlier.

Now ```cd()``` into the ```TrkAnaNeg()``` folder and ```.ls``` the directory to see the trkana tree:

```
root [2] TrkAnaNeg->cd()
(bool) true
root [3] .ls
TDirectoryFile*         TrkAnaNeg       TrkAnaNeg (TrkAnaTreeMaker) folder
 KEY: TTree     trkana;6        track analysis [current cycle]
 KEY: TTree     trkana;5        track analysis [backup cycle]
```

Now we can ```Print()``` to see the branches of the tree:

```
root [4] trkana->Print()
(...snip...)
```

There are a lot of branches... These are documented [elsewhere](https://mu2ewiki.fnal.gov/wiki/TrkAna#Tree_Structure) but we will go through the important ones in later tutorial exercises.

We can ```Scan()``` through the tree to see information on each track. Here we are picking out the run id, subrun id, and event id of the event; and also the magnitude of the momentum of first fit result of the track (```demfit[0].mom.R()```):

```
root [5] trkana->Scan("evtinfo.runid:evtinfo.subrunid:evtinfo.eventid:demfit[0].mom.R()")
************************************************************
*    Row   * evtinfo.r * evtinfo.s * evtinfo.e * demfit[0] *
************************************************************
*        0 *      1210 *         0 *         1 * 103.06026 *
*        1 *      1210 *         0 *         4 * 104.14388 *
*        2 *      1210 *         0 *         7 * 97.289207 *
*        3 *      1210 *         0 *        14 * 102.12971 *
*        4 *      1210 *         0 *        15 * 103.87315 *
*        5 *      1210 *         0 *        19 * 103.41012 *
*        6 *      1210 *         0 *        21 * 103.46038 *
*        7 *      1210 *         0 *        23 * 104.61264 *
*        8 *      1210 *         0 *        24 * 103.32880 *
```


## Python

The python exercise can be run either in a 

To open and inspect the TrkAna ROOT file with python, we will use [uproot](https://uproot.readthedocs.io/en/latest/index.html).

Open up a  and in the first cell, we will import uproot:

```
import uproot
```

Run the cell by pressing ctrl+enter.

In the next cell we can open up the file and look at its contents like this:

```
file = uproot.open("nts.brownd.CeEndpointMix1BBSignal.MDC2020z_TKAv04.tka")
file.keys()
```

which will produce the output:

```
['TrkAnaNeg;1', 'TrkAnaNeg/trkana;6', 'TrkAnaNeg/trkana;5', 'TrkAnaPos;1', 'TrkAnaPos/trkana;1', 'genCountLogger;1', 'genCountLogger/numEvents;1', 'genCountLogger/numSubRuns;1']
```

where we see that uproot has descended into each of the three top-level directories listed earlier to get the contents of each.

The TrkAna tree can be accessed and the branches inspected by doing:

```
trkana = file["TrkAnaNeg"]["trkana"]
trkana.keys()
```

which will produce a lot of output since there are a lot of branches. These are documented [elsewhere](https://mu2ewiki.fnal.gov/wiki/TrkAna#Tree_Structure) but we will go through the important ones in later tutorial exercises.

Note that getting the TrkAna tree can be done in a single step like this:

```
trkana = uproot.open("nts.brownd.CeEndpointMix1BBSignal.MDC2020z_TKAv04.tka:TrkAnaNeg/trkana")
```

With ```trkana``` defined we can now get its contents using the ```arrays()``` function. This function reads the data into an [awkward array](https://awkward-array.org/doc/main/). A brief note on this: in HEP we often have different numbers of physics objects in each event, and so they will now fit efficiently into fixed-length arrays. For example, if we want to store the straw hits in the tracker, there will be a different number in each event. Therefore we need to use "awkward" or "ragged" arrays, which requires the use of the awkward array package. This is the default library used by uproot to read branches.

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

You may notice that this is slow. The ```arrays()``` function has an option to filter branches so that you only read in the data you want. For example:

```
branches = trkana.arrays(filter_name=["/evtinfo.*id/", "/demfit.mom.*/"])
print(branches.fields)
```

will read in the just the ```evtinfo.*``` and ```demfit.mom.*``` branches.

Then you can inspect these branches with ```branches[N:M]```


### Python Script

A python script called ```Opening.py``` with the following content will perform the same commands as covered in the above [python](#Python) example:

```
import uproot # for reading in ROOT files

filename="nts.brownd.CeEndpointMix1BBSignal.MDC2020z_TKAv04.tka"
treename="TrkAnaNeg/trkana"

# Open the ROOT file and be read yto read in the trkana tree
trkana = uproot.open(filename+":"+treename)

# Read in just the evtinfo id branches, and the demfit.mom branches
branches = trkana.arrays(filter_name=["/evtinfo.*id/", "/demfit.mom.*/"])

# Print the first 20 tracks
print(branches[:20])
```

which can be run with:

```
python3 Opening.py
```

## Additional Exercises
Try some of the following additional exercises:

* open up the ```TrkAnaPos``` TrkAna tree and get the number of downstream e-plus tracks

Last Page: [Logging In and Setting Up](setup.md)

Next Page: [Plotting Global Track Information](n-hits.md)
