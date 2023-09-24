# Opening and Inspecting a TrkAna ROOT file

In this exercise, we will open the TrkAna ROOT file and inspect the TrkAna TTree and its branches.

## ROOT Command Line

With the ROOT command line, we open the TrkAna ROOT file like so:

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

Now ```cd()``` into the ```TrkAnaNeg()``` folder and ```.ls``` the directory to see the trkana tree:

```
root [2] TrkAnaNeg->cd()
(bool) true
root [3] .ls
TDirectoryFile*         TrkAnaNeg       TrkAnaNeg (TrkAnaTreeMaker) folder
 KEY: TTree     trkana;6        track analysis [current cycle]
 KEY: TTree     trkana;5        track analysis [backup cycle]
```

(Note that there are two ```trkanas``` for ROOT reasons)

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

## ROOT Macro

Instead of typing all the commands each time, we can write a ROOT macro called ```Opening.C``` with the following contents:

```
void Opening() {

     // Open the TrkAna ROOT file for reading
     TFile* file = new TFile("nts.brownd.CeEndpointMix1BBSignal.MDC2020z_TKAv4.tka", "READ");

     // Get the TrkAna tree from the file. (Note that the (TTree*) is needed to "cast" the object to the correct class)
     TTree* trkana = (TTree*) file->Get("TrkAnaNeg/trkana");

     trkana->Print();
     trkana->Scan("evtinfo.runid:evtinfo.subrunid:evtinfo.eventid:demfit[0].mom.R()");
}
```

which can be run like so:

```
root -l Opening.C
```


## Python

To open and inspect the TrkAna ROOT file with python, we will use [```uproot```](https://uproot.readthedocs.io/en/latest/index.html)
