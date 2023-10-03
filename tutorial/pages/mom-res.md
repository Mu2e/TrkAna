# Plotting MC Truth Information of the Track

## Objectives

In this exercise, you will learn:

* about the ```demmcvd``` branch that stores MC truth information of tracked particles at virtual detectors, and 
* how to compare MC truth and reconstructed information

## Contents

* [Common Introduction](#Common-Introduction)
* [ROOT](#ROOT)
* [Python](#Python)
* [Additional Exercises](#Additional-Exercises)

## Common Introduction

We want to compare the reconstruction with the MC truth from the simulation to see how well the reconstruction is doing. For the reconstructed track momentum, we have values at the entrance, middle, and exit to the tracker. For the MC truth particle momentum, we have values at the same locations as recorded by [virtual detectors](https://mu2ewiki.fnal.gov/wiki/Simulation#virtual_detectors) in the simulation.

In TrkAna we store the MC truth information for the particle as it passes through virtual detectors in the ```demmcvd``` branch. Like the ```demfit``` branch it is also an array and has an ```sid``` leaf to identify the surface it corresponds to.

One important point: the ```demmcvd``` and the ```demfit``` arrays are not in lock-step. i.e. the first element of the ```demmcvd``` array may correspond to the tracker entrance, but the first elements of the ```demfit``` branch may not e.g. if the fit fails at the tracker entrance. For this reason, the ```demmcvd``` branch also has a ```iinter``` leaf which is the element in the ```demfit``` array to compare to.

## ROOT

In ROOT, let's open the file, get the tree, and create a TCanvas as before:

```
TFile* file = new TFile("nts.brownd.CeEndpointMix1BBSignal.MDC2020z1_best_v1_1_std_v04_01_00.tka", "READ");
TTree* trkana = (TTree*) file->Get("TrkAnaNeg/trkana");

TCanvas* c1 = new TCanvas("c1", "c1");
c1->SetGridx(true);
c1->SetGridy(true);
```

We can first plot the reconstructed momentum and the MC truth information separately:

```
trkana->Draw("demfit.mom.R()>>hist(100,100,110)", "demfit.sid==0", "HIST");
trkana->Draw("demmcvd.mom.R()>>hist2", "demmcvd.sid==0", "HIST SAMES");
```

If you check the number of entries in each histogram with ```hist->GetEntries()``` you will notice that they are different. So to get the momentum resolution (the difference between the two), we have to do the following:


```
trkana->Draw("demfit[demmcvd.iinter].mom.R() - demmcvd.mom.R()", "demmcvd.sid==0", "HIST");
```

If you want to plot this on a log scale, then you use the command:

```
c1->SetLogy(true);
```


## Python

In python, we can set up as normal but add the ```demmcvd``` branch to our list of branches that we read in:

```
import uproot
import matplotlib.pyplot as plt
import awkward as ak

trkana = uproot.open("nts.brownd.CeEndpointMix1BBSignal.MDC2020z1_best_v1_1_std_v04_01_00.tka:TrkAnaNeg/trkana")

fig, ax = plt.subplots(1,1)

branches = trkana.arrays(filter_name=["/demfit[.]*/", "/demlh[.]*/", "/demmcvd[.]*/"])
```

Then we calculate the magnitude of the momentum as we did in the last exercies:

```
branches['demfit.mom'] = (branches['demfit.mom.fCoordinates.fX']**2 + branches['demfit.mom.fCoordinates.fY']**2 + branches['demfit.mom.fCoordinates.fZ']**2)**0.5
branches['demmcvd.mom'] = (branches['demmcvd.mom.fCoordinates.fX']**2 + branches['demmcvd.mom.fCoordinates.fY']**2 + branches['demmcvd.mom.fCoordinates.fZ']**2)**0.5
```



## Additional Exercises
Here are some additional exercises, you might want to try:

* try making some cuts on the track parameters to see if the momentum resolution changes


Last Page: [Plotting Local Track Information](reco-mom.md)

Next Page: [Plotting MC Truth Information of the Particle](e-loss.md)
