# Plotting Global Track Information

## Objectives

In this exercise, you will:

* learn about the ```dem``` branch that contains , and
* plot the number of hits on each track.

## Contents

* [Common Introduction](#Common-Introduction)
* [ROOT](#ROOT)
    * [Making ROOT plots informative](#Making-ROOT-plots-informative)
* [Python](#Python)
    * [Making python plots informative](#Making-python-plots-informative)

## Common Introduction

Each entry in the TrkAna tree corresponds to a single candidate track. Information about the candidate track as a whole is stored in the ```dem``` branch. The leaves of the ```dem``` branch are defined [here](https://github.com/Mu2e/TrkAna/blob/v04_00_00/inc/TrkInfo.hh#L57).

Note that the same type of branch exists also for the supplemental tracks: upstream e-minus (```uem``` branch), and downstream mu-minus (```dmm``` branch).

## ROOT

From the ROOT command line, after you have opened the TrkAna ROOT file and ```cd```'d into the TrkAnaNeg directory. You can see all the leaves on the ```dem``` branch with:

```
trkana->Print("dem.*")
```

And then you can plot one of the leaves like so:

```
trkana->Draw("dem.nhits>>hist(100,0,100)")
```

You could also plot the number of hits that were actually used in the track fit ("active") on the same set of axes:

```
trkana->Draw("dem.nactive>>hist2", "", "SAME")
```

### Making ROOT plots informative

All plots should have axis labels, titles, legends, stats boxes, and grids. Here are pointers to adding these:

* setting histogram title
    * ```hist->SetTitle("Hist Title")```
* setting axis labels
    * ```hist->GetXaxis()->SetTitle("x-axis title")```
* setting grid lines
    * create a ```TCanvas``` before drawing: ```TCanvas* c1 = new TCanvas("c1", "c1");```
    * set the grid: ```c1->SetGridx()```
* setting different colors
    * ```hist->SetLineColor(kRed)```
* adding a legend
    * create a legend: ```TLegend* leg = new TLegend()```
    * add entries: ```leg->AddEntry(hist, "all hits", "l");```
    * draw the legend: ```leg->Draw()```


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

### Making ROOT plots informative

All plots should have axis labels, titles, legends, stats boxes, and grids. Here are pointers to adding these:


Last Page: [Opening and Inspecting a TrkAna ROOT file](opening.md)

Next Page: [Plotting Local Track Information](reco-mom.md)
