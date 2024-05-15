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

Each entry in the TrkAna tree corresponds to a Mu2e event. Information about the all the downstream e-minus tracks in the event are stored in the ```dem``` branch. The leaves of the ```dem``` branch are defined [here](https://github.com/Mu2e/TrkAna/blob/v05_00_00rc/inc/TrkInfo.hh#L57).

The ```dem``` branch is an array.

## ROOT

In ROOT, in order to handle multiple files, we will use a [TChain](https://root.cern.ch/doc/v628/classTChain.html) which we can use like a TTree. We create a TChain like this:

```
TChain* trkana = new TChain("TrkAna/trkana");
```

Now we need to add TrkAna files to this. Unfortunately, the ```Add()``` command does not accept wildcards in directories, so we have to loop through the filelist ourselves and add them one at a time:

```
std::ifstream input_filelist("filelists/nts.mu2e.CeEndpointMix1BBSignal.Tutorial_2024_03.list");
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

ROOT will automatically loop through the ```dem``` array so we can plot a histogram of the number of hits in all tracks like so:

```
TH1D* hist = new TH1D("hist", "", 100,0,100)
trkana->Draw("dem.nhits>>hist", "", "goff");
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

The last thing we want to do is apply an event-level cut (i.e. only plot the information from events that pass some condition). Here we will select events that have two downstream e-minus tracks. To do this we apply the cut to the second argument of the ```Draw()``` function:

trkana->Draw("dem.nactive>>hist3", "tcnt.ndem==2", "goff");



## Python
In python, to handle multiple files we will use uproot but will also need to use some functions from numpy and awkward so we import those too:

```
import uproot
import matplotlib.pyplot as plt
import numpy as np
import awkward as ak
```

To plot data from multiple TrkAna files, we will use ```uproot.iterate```. We can use it similarly to the ```arrays()``` function in the [last exercise](opening.md#Python) where we filter on the branches we want. To show the structure of things, we will first print the ```dem.nhits``` arrays:

```
for batch in uproot.iterate(files=wildcarded_dir+":TrkAna/trkana", filter_name=["/tcnt/", "/dem/"], step_size='10 MB'):
    print(batch['dem.nhits'])
```
where ```wildcarded_dir``` is string for the location of all the files. You can get this by looking in the filelist and replacing any unique parts of a filename with a ```*```. It will look something like ```/abs/path/to/datasets/*/*/*.tka```. The ```step_size='10MB'``` argument means that uproot will only read 10 MB of memory at time. The argument also accepts integers, which is interpreted as a number of entries in the TTree.


The output will be something like: 

```
[[37], [26], [51], [51], [59], [45], ..., [25], [42], [50], [27], [17], [33]]
```
where you will see that we have an array of arrays.

In order to make a histogram, we need to "flatten" the awkward arrays so that we have one array:

```
for batch in uproot.iterate(files=wildcarded_dir+":TrkAna/trkana", filter_name=["/tcnt/", "/dem/"], step_size='10 MB'):
    print(ak.flatten(batch['dem.nhits']))
```

which will produce output like this:

```
[37, 26, 51, 51, 59, 45, 36, 54, 23, ..., 47, 44, 41, 25, 42, 50, 27, 17, 33]
```

Now that we know how to put everything into one array, we can iterate and build up an array of all the hits like this:

```
dem_nhits=[] # create an array to store the results
for batch in uproot.iterate(files=wildcarded_dir+":TrkAna/trkana", filter_name=["/tcnt/", "/dem/"], step_size='10 MB'):
    dem_nhits = np.append(dem_nhits, ak.flatten(batch['dem.nhits'])) # append to the array
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

The last thing we want to do is apply an event-level cut (i.e. only plot the information from events that pass some condition). Here we will select events that have two downstream e-minus tracks. To do this we will create a "mask array", which is an array of the same shape and dimensionality as our data but containing either ```True``` or ```False```::

```
tcnt_ndem2_mask = (batch['tcnt.ndem']==2)
```

this is just an array of booleans. (You can ```print(tcnt_ndem2_mask)``` to see this).

Then we use the mask like this:

```
batch[(tcnt_ndem2_mask)]['dem.nhits']
```


One other option for ```uproot.iterate``` that you might want to use is to report every step. This can be done like so:

```
for batch, report in uproot.iterate(files=wildcarded_dir+":TrkAna/trkana", filter_name=["/dem/"], step_size='10 MB', report=True):
    print(report).
    dem_nhits = np.append(dem_nhits, batch['dem.nhits'])
```


## Additional Exercises

If you like, try some of the following:

* plot the number of hits on other track types
* make some different event-level cuts
* inspect the leaves on the ```dem``` branch and plot something else


Last Page: [Opening and Inspecting a TrkAna ROOT file](opening.md)

Next Page: [Plotting Local Track Information](reco-mom.md)
