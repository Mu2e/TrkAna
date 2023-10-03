# Plotting Global Track Information

## Objectives

In this exercise, you will:

* learn about the ```dem``` branch that contains global track information, and
* plot the number of hits on each track.

## Contents

* [Common Introduction](#Common-Introduction)
* [ROOT](#ROOT)
* [Python](#Python)
* [Additional Exercises](#Additional-Exercises)

## Common Introduction

Each entry in the TrkAna tree corresponds to a single candidate track. Information about the candidate track as a whole is stored in the ```dem``` branch. The leaves of the ```dem``` branch are defined [here](https://github.com/Mu2e/TrkAna/blob/v04_01_00/inc/TrkInfo.hh#L57).

Note that the same type of branch exists also for the supplemental tracks: upstream e-minus (```uem``` branch), and downstream mu-minus (```dmm``` branch).

## ROOT

In ROOT, we start by opening the ROOT file and getting the TrkAna tree:

```
TFile* file = new TFile("nts.brownd.CeEndpointMix1BBSignal.MDC2020z1_best_v1_1_std_v04_01_00.tka", "READ");
TTree* trkana = (TTree*) file->Get("TrkAnaNeg/trkana");
```

Then we create a [TCanvas](https://root.cern.ch/doc/v628/classTCanvas.html) to put the plot on:

```
TCanvas* c1 = new TCanvas("c1", "c1");
```

We will want to have gridlines on the plot:

```
c1->SetGridx(true);
c1->SetGridy(true);
```

We can then plot a histogram of the number of hits on each track like so:

```
trkana->Draw("dem.nhits>>hist(100,0,100)", "", "goff");
```

where ```goff``` is the drawing option to now draw since we are still missing some important information: axis labels

```
hist->GetXaxis()->SetTitle("Number of Hits");
hist->GetYaxis()->SetTitle("Number of Tracks");
```

Now we can draw the histogram:

```
hist->Draw("HIST");
```

You could also plot the number of hits that were actually used in the track fit ("active") on the same set of axes:

```
trkana->Draw("dem.nactive>>hist2", "", "goff");
```

Before drawing, we will want to change the line color of this histogram::

```
hist2->SetLineColor(kRed);
hist2->Draw("HIST SAME");
```

Finally, we need a [TLegend](https://root.cern.ch/doc/v628/classTLegend.html) to document what the two histograms are:

```
TLegend* leg = new TLegend()
leg->AddEntry(hist, "total number of hits", "l")
leg->AddEntry(hist2, "total number of active hits", "l")
leg->Draw()
```


## Python
To make plots in python, we need to use matplotlib so we import it along with uproot:

```
import uproot
import matplotlib.pyplot as plt
```

We then open the TrkAna file and get ready to read the TrkAna tree:

```
trkana = uproot.open("nts.brownd.CeEndpointMix1BBSignal.MDC2020z1_best_v1_1_std_v04_01_00.tka:TrkAnaNeg/trkana")
```

Next we filter the branches so that we just read in the ```dem``` branch using a regular expression:

```
branches = trkana.arrays(filter_name=["/dem[.]*"])
```

Next, we get a figure and a set of axes ready to be drawn on:

```
fig, ax = plt.subplots(1,1)
```

We can then plot a histogram of the number of hits on each track like so:

```
ax.hist(branches['dem.nhits'], bins=100, range=(0,100), label='total number of hits', histtype='step')
```

Now we can make the plot more informative with grid lines and axis labels:

```
ax.set_xlabel('Number of Hits')
ax.set_ylabel('Number of Tracks')
ax.grid(True)
```

You could also plot the number of hits that were actually used in the track fit ("active") on the same set of axes:

```
ax.hist(branches['dem.nactive'], bins=100, range=(0,100), label='total number of used hits', histtype='step')
```

Since we have two histograms, we should add a legend like so:

```
ax.legend()
```

Finally, we need to ```show``` the plot:

```
plt.show()
```



## Additional Exercises

If you like, try some of the following:

* plot the number of hits on the upstream e-minus, and downstream mu-minus tracks
* inspect the leaves on the ```dem``` branch and plot something else


Last Page: [Opening and Inspecting a TrkAna ROOT file](opening.md)

Next Page: [Plotting Local Track Information](reco-mom.md)
