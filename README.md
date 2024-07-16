# TrkAna

## Introduction

TrkAna is an event-based ntuple for Mu2e analyses. Each entry in the ntuple corresponds to a single Mu2e event. 

## Validation

We want to make sure that any changes we make to the code doesn't change the content of the TrkAna ntuple.

Before making any changes, create a TrkAna file and run the validation script. This creates a new ROOT file with histograms created from the TrkAna ntuple:

```
mu2e -c TrkAna/fcl/TrkAnaReco.fcl -S filelist.txt --TFileName nts.trkana.before.root

root -l -b validation/create_val_file.C\(\"nts.trkana.before.root\", \"val.trkana.before.root\"")
```

Then make your changes, rebuild the code and then re-run:

```
mu2e -c TrkAna/fcl/TrkAnaReco.fcl -S filelist.txt --TFileName nts.trkana.after.root

root -l -b validation/create_val_file.C\(\"nts.trkana.after.root\", \"val.trkana.after.root\"")
```

Finally, to compare the two sets of histograms we use [valCompare](https://mu2ewiki.fnal.gov/wiki/Validation#valCompare)

```
valCompare -p trkana-validation-booklet.pdf -r val.trkana.before.root val.trkana.after.root
```

We should will have perfect matches between all histograms. However, in some rare instances, we may expect differences. If you see any non-perfect matches, then discuss with the TrkAna experts.


## Useful Links

* [Mu2eWiki page](https://mu2ewiki.fnal.gov/wiki/TrkAna)
* [spreadsheet explaining branch and leaf names](https://docs.google.com/spreadsheets/d/1IMZVgj74vxGTWqAFRtFEEcYChujJyc38VcopZh52jhc/edit)
* [version history of TrkAna](https://mu2ewiki.fnal.gov/wiki/TrkAna#Version_History_.2F_TrkAna_Musings)
* [tutorial](tutorial/README.md) (some but not all updated for v5)
* [instructions for developers](https://mu2ewiki.fnal.gov/wiki/TrkAna#For_Developers)
