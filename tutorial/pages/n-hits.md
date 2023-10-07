# Plotting Global Track Information

## Objectives

In this exercise, you will:

* learn about the ```dem``` branch that contains global track information,
* handle multiple TrkAna files, and
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

In ROOT, in order to handle multiple files, we will use a [TChain](https://root.cern.ch/doc/v628/classTChain.html) which we can use like a TTree that we create like this:

```
TChain* trkana = new TChain("TrkAnaNeg/trkana");
```

Now we need to add TrkAna files to this. Unfortunately, the ```Add()``` command does not accept wildcard in directories, so we have to loop through the filelist ourselves and add them one at a time:

```
std::ifstream input_filelist("filelists/nts.mu2e.CeEndpointMix1BBSignal.MDC2020z1_best_v1_1_std_v04_01_00.list");
if (input_filelist.is_open()) {
  std::string filename;
  while(std::getline(input_filelist,filename)) {
    trkana->Add(filename.c_str());
  }
  input_filelist.close();
}
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
In python, to handle multiple files we will use uproot but will also need to use some functions from numpy so we will import that:

```
import uproot
import matplotlib.pyplot as plt
import numpy as np
```

Then instead of opening a single TrkAna file, we will use ```uproot.iterate```. Before that, we need to make some arrays to keep track of the data we want to plot. In this exercise, we will plot the number of hits on each track:

```
dem_nhits=[]
```

Now we can iterate through the files like so, filtering the branches like we did in the [last exercise](opening.md#Python):

```
for batch in uproot.iterate(files=wildcarded_dir+":TrkAnaNeg/trkana", filter_name=["/dem[.]*"], step_size='10 MB'):
    dem_nhits = np.append(dem_nhits, batch['dem.nhits'])
```

where ```wildcarded_dir``` is string for the location of all the files. You can get this by looking in the filelist and replacing any unique parts of a filename with a ```*```. It will look something like ```/abs/path/to/datasets/*/*/*.tka```.

The ```step_size='10MB'``` argument means that uproot will only read 10 MB of memory at time. The argument also accepts integers, which is interpreted as a number of entries in the TTree.

One other option for ```uproot.iterate``` that you might want to use is to report every step. This can be done like so:

```
for batch, report in uproot.iterate(files=wildcarded_dir+":TrkAnaNeg/trkana", filter_name=["/dem[.]*"], step_size='10 MB', report=True):
    print(report).
    dem_nhits = np.append(dem_nhits, batch['dem.nhits'])
```


Now we can get to plotting. First, we get a figure and a set of axes ready to be drawn on:

```
fig, ax = plt.subplots(1,1)
```

We can then plot a histogram of the number of hits on each track like so:

```
ax.hist(dem_nhits, bins=100, range=(0,100), label='total number of hits', histtype='step')
```

Now we can make the plot more informative with grid lines and axis labels:

```
ax.set_xlabel('Number of Hits')
ax.set_ylabel('Number of Tracks')
ax.grid(True)
```

You can also plot the number of hits that were actually used in the track fit ("active") on the same set of axes. You will need to make a ```dem_nactive``` array and fill it during the ```uproot.iterate``` loop, you can then do:

```
ax.hist(dem_nactive, bins=100, range=(0,100), label='total number of used hits', histtype='step')
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
