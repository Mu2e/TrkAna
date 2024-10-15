# EventNtuple

## Table of Contents
1. [Introduction](#Introduction)
2. [Structure](#Structure)
3. [How to Analyze an EventNtuple](#How-to-Analyze-an-EventNtuple)
4. [How to Create an EventNtuple](#How-to-Create-an-EventNtuple)
5. [Validation](#Validation)
6. [Previous Verisons](#Previous-Versions)
   - [Upgrading from v5 to 6](#Upgrading-from-v5-to-v6)
7. [Other Useful Links](#Other-Useful-Links)

## Introduction

The EventNtuple is a simplified data format that can be used for Mu2e analyses.

## Structure
The EventNtuple structure is complex.

The help understand what all the branches and leaves mean, we have an [```ntuplehelper```](doc/ntuplehelper.md) tool

## How to Analyze an EventNtuple
To help with analyzing the EventNtuple given its complex structure, we have two sets of utilities:
* [RooUtil](utils/rooutil/README.md) for ROOT-based analyses, and
* [PyUtil](utils/pyutil/README.md) for python-based analyses.

Both of these are currently undergoing rapid development. Feel free to use these prototypes and let us know your thoughts.

## How to Create an EventNtuple
In case you need to create your own EventNtuple you can do the following from a clean login in your working directory with the list of files you want to run over in a text file called ```your-art-filelist.txt```:

```
mu2einit
muse setup EventNtuple
mu2e -c EventNtuple/fcl/from_mcs-mockdata.fcl -S your-art-filelist.txt
```

This will create a file called ```nts.owner.description.version.sequencer.root``` that contains the EventNtuple. The EventNtuple will then be in the ROOT file as ```EventNtuple/ntuple```.

Note: Other fcl files are available. See table [here](fcl/README.md) to see if another one is more appropriate for your use case.

## Validation
Validation scripts and instructions are [here](validation/README.md)

## Previous Versions
The version history of EventNtuple is [here](https://mu2ewiki.fnal.gov/wiki/EventNtuple).

### Upgrading from v5 to v6
* For analyzers: a list of branch/leaf/name changes is [here](doc/v5-to-v6.md)
* For developers: instructions to update your development area are [here](doc/v5-to-v6_developers.md)

## Other Useful Links

* [Mu2eWiki page](https://mu2ewiki.fnal.gov/wiki/EventNtuple)
* [tutorial](tutorial/README.md)
