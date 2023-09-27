# Plotting Global Track Information

## Objectives

In this exercise, you will:

* learn about the ```dem``` branch that contains global track information, and
* plot the number of hits on each track.

## Contents

* [Common Introduction](#Common-Introduction)
* [ROOT](#ROOT)
* [Python](#Python)

## Common Introduction

Each entry in the TrkAna tree corresponds to a single candidate track. Information about the candidate track as a whole is stored in the ```dem``` branch. The leaves of the ```dem``` branch are defined [here](https://github.com/Mu2e/TrkAna/blob/v04_00_00/inc/TrkInfo.hh#L57).

Note that the same type of branch exists also for the supplemental tracks: upstream e-minus (```uem``` branch), and downstream mu-minus (```dmm``` branch).

## ROOT

In ROOT, after opening the ROOT file and getting the TrkAna tree, we want to create a [TCanvas](https://root.cern.ch/doc/v628/classTCanvas.html) to put the plot on:

```
TCanvas* c1 = new TCanvas("c1", "c1");
```

We can then plot a histogram of the number of hits on each track like so:

```
trkana->Draw("dem.nhits>>hist(100,0,100)", "", "goff")
```

where ```goff``` is the drawing option to now draw yet since we are still missing some important information: axis labels

```
hist->GetXaxis()->SetTitle("N Hits");
hist->GetYaxis()->SetTitle("Number of Tracks");
```

Now we can draw the histogram:

```
hist->Draw("HIST");
```

You could also plot the number of hits that were actually used in the track fit ("active") on the same set of axes:

```
trkana->Draw("dem.nactive>>hist2", "", "HIST SAME")
```

Since the colors are the same, we will want to change that:

```
hist2->SetLineColor(kRed)
hist2->Draw("HIST SAME")
```

where the last line is because we need to redraw to see the changes.

Finally, we need a [TLegend](https://root.cern.ch/doc/v628/classTLegend.html) to document what the two histograms are:

```
TLegend* leg = new TLegend()
leg->AddEntry(hist, "all hits", "l")
leg->AddEntry(hist2, "n active hits", "l")
leg->Draw()
```


## Python
To make plots in python, you will need to use matplotlib:

```
import matplotlib.pyplot as plt
```



```
branches = trkana.arrays(filter_name=["/dem[.]*"])
```

where ```filter_name``` is using a regular expression to get only the ```dem``` branches.

```
plt.hist(branches['dem.nhits'], bins=100, range=(0,100), label='nhits', histtype='step')
plt.show()
```



Last Page: [Opening and Inspecting a TrkAna ROOT file](opening.md)

Next Page: [Plotting Local Track Information](reco-mom.md)
