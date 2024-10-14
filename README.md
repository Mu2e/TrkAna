# EventNtuple

## Introduction

The EventNtuple is a simplified data format that can be used for Mu2e analyses.

## Structure
The EventNtuple structure is complex.

The help understand what all the branches and leaves mean, we have an [```ntuplehelper```](doc/ntuplehelper.md) tool

## Utilities
To help with analyzing the EventNtuple given its complex structure, we have two sets of utilities:
* [RooUtil](utils/rooutil/README.md) for ROOT-based analyses, and
* [PyUtil](utils/pyutil/README.md) for python-based analyses.

Both of these are currently undergoing rapid development. Feel free to use these and let us know your thoughts.

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
