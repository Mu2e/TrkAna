# How to Create a ROOT MakeClass

ROOT MakeClass is a way to perform event loop analyses and can be generated for TrkAna. More information on ROOT MakeClass is available [here](https://root.cern.ch/root/htmldoc/guides/users-guide/Trees.html#using-ttreemakeclass)

## Instructions

Here are the instructions to generate a ROOT MakeClass for TrkAna.

* Log in to a mu2egpvm machine

```
mu2einit
cd /to/your/work/area/
muse setup TrkAna
root -l trkana.root
```

* You are now in the ROOT command line. Do:

```
TrkAna->cd()
trkana->MakeClass("name_of_analyzer")
```

This will generate the ```name_of_analyzer.hh``` and ```name_of_analyzer.C``` file
