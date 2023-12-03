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
TChain* trkana = new TChain("TrkAnaNeg/trkana");

std::ifstream input_filelist("filelists/nts.mu2e.CeEndpointMix1BBSignal.MDC2020z1_best_v1_1_std_v04_01_00.list");
if (input_filelist.is_open()) {
  std::string filename;
  while(std::getline(input_filelist,filename)) {
    trkana->Add(filename.c_str());
  }
  input_filelist.close();
}


TCanvas* c1 = new TCanvas("c1", "c1");
c1->SetGridx(true);
c1->SetGridy(true);
```

We can first plot the reconstructed momentum and the MC truth information separately:

```
trkana->Draw("demfit.mom.R()>>hist(100,100,110)", "demfit.sid==0", "HIST");
trkana->Draw("demmcvd.mom.R()>>hist2", "demmcvd.sid==0", "HIST SAMES");
```

If you check the number of entries in each histogram with ```hist->GetEntries()``` you will notice that they are different. This is because sometimes one array or the other is missing an intersection. So to get the momentum resolution (the difference between the two), we have to make sure we are comparing apples with apples:

```
trkana->Draw("demfit[demmcvd.iinter].mom.R() - demmcvd.mom.R()", "demmcvd.sid==0", "HIST");
```

As explained in the introduction to this exercise, the ```demfit``` and ```demmcvd``` branches can be out of sync and so we use the ```demmcvd.iinter``` to compare reco and MC at the same intersection. You can get a better idea of this issue by scanning the TTree for entries where they don't match:

```
trkana->Scan("demfit.mom.R():demfit.sid:demmcvd.mom.R():demmcvd.sid:demmcvd.iinter", "demfit.sid!=demmcvd.sid")
```

taking note of a ```Row``` number and then looking at that entry directly:

```
trkana->Scan("demfit.mom.R():demfit.sid:demmcvd.mom.R():demmcvd.sid:demmcvd.iinter", "Entry$==XXX")
```

You might want to put the plot on a log scale, which you can do with this command:

```
c1->SetLogy(true);
```


## Python

In python, we can set up as normal but add the ```demmcvd``` branch to our list of branches that we read in:

```
import uproot
import matplotlib.pyplot as plt
import numpy as np
import awkward as ak

for batch, report in uproot.iterate(files=wildcarded_dir+":TrkAnaNeg/trkana", filter_name=["/demfit/", "/demlh/", "/demmcvd/"], step_size="10 MB", report=True):
    print(report)


fig, ax = plt.subplots(1,1)
```

Before the iterate loop, we will create arrays for the reco and MC momentum:

```
trk_ent_mom=[]
mc_trk_ent_mom=[]
```

Within the iterate loop, we will calculate the magnitude of the momentum as we did in the last exercies and add one for the ```demmcvd``` branch:

```
    batch['demfit_mom'] = np.sqrt((batch['demfit']['mom']['fCoordinates']['fX'])**2 + (batch['demfit']['mom']['fCoordinates']['fY'])**2 + (batch['demfit']['mom']['fCoordinates']['fZ'])**2)
    batch['demmcvd_mom'] = np.sqrt(batch['demmcvd']['mom']['fCoordinates']['fX']**2 + batch['demmcvd']['mom']['fCoordinates']['fY']**2 + batch['demmcvd']['mom']['fCoordinates']['fZ']**2)
```

We will also create masks so that we get fit information at the entrance to the tracker:

```
    trk_ent_mask = (batch['demfit']['sid']==0)
    mc_trk_ent_mask = (batch['demmcvd']['sid']==0)
```

If you were to print the lengths of these arrays (with e.g. ```print(len(ak.flatten(trk_ent_mask)), len(ak.flatten(mc_trk_ent_mask)))```), you will see that they have different sizes. In order to compare apples to apples, we want to only look at events where both reco and MC have this information. Additionally, because these masks are fit arrays, and we want to make an "event" array, we need to use the ```ak.any()``` function:

```
    has_trk_ent = ak.any(trk_ent_mask, axis=2, keepdims=True)
    has_mc_trk_ent = ak.any(mc_trk_ent_mask, axis=2, keepdims=True)
```

To explain this a bit more: the ```trk_ent_mask``` will look like this:

```
[[[True, False, False]], [[True, ..., False]], ..., [[True, False, False]]]
```

where the innermost arrays are the three different fit locations (entrance, middle, and exit of the tracker), the next array out are the dem trackes, and the outer array is for each Mu2e event.

What ```ak.any()``` does is takes the logical OR of each inner array and we set ```axis=2``` and ```keepdims=True``` so that we maintain the same shape and make:

```
[[[ True ]], [[ True ]], ... [[ False ]]]
```

Going back to our iterate function, we then want a mask for events that have both reco and MC information at the tracker entrance:

```
    has_both = (has_trk_ent) & (has_mc_trk_ent)
```

Finally, we then apply the cuts and fill our arrays like so:

```
    trk_ent_mom = np.append(trk_ent_mom, ak.flatten(batch[(has_both) & (trk_ent_mask)]['demfit_mom'], axis=None))
    mc_trk_ent_mom = np.append(mc_trk_ent_mom, ak.flatten(batch[(has_both) & (mc_trk_ent_mask)]['demmcvd_mom'], axis=None))
```

where we are using both an event-level mask (```has_both```) and a track-level mask (```trk_ent_mask```, ```mc_trk_ent_mask```), and ```axis=None``` flattens the arrays to one-dimension.

To make and draw the plot we want to take the difference between the reconstruction and the MC truth:

```
mom_res = trk_ent_mom - mc_trk_ent_mom
ax.hist(mom_res, bins=100, range=(-10,10), label='all tracks', histtype='step', log=True)
```


## Additional Exercises
Here are some additional exercises, you might want to try:

* try making some cuts on the track parameters to see if the momentum resolution changes


Last Page: [Plotting Local Track Information](reco-mom.md)

Next Page: [Plotting MC Truth Information of the Particle](start-pos.md)
