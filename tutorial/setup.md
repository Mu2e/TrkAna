# Logging In and Setting Up

## Objectives

In this exercise, you will learn how to:

* set up

## Contents

* [Common Introduction](#Common-Introduction)
* [ROOT](#ROOT)
* [Python](#Python)
** [Python Note

## Common Introduction



## ROOT

For ROOT exercises, you should log in to a mu2egpvm machine:

```
ssh -XY username@mu2egpvm0X.fnal.gov
cd to/your/working/area/
setup mu2e
muse setup TrkAna v04_00_00
```

where ```mu2egpvm0X``` is between ```mu2egpvm01``` and ```mu2egpvm06```.

## Python

For python exercises using jupyter notebooks, you should log into to a mu2egpvm machine and do some port forwarding:

```
ssh -XY -L YYYY:localhost:YYYY username@mu2egpvm0X.fnal.gov
cd to/your/working/area/
setup mu2e
muse setup TrkAna v04_00_00
setup pyana v1_05_00
```

where ```YYYY``` is a port number (e.g. 3000, 3001) that you will use to open a browser on your local machine. [Pyana](https://mu2ewiki.fnal.gov/wiki/Pyana) is a UPS package that provides a common python environment for all Mu2e analyzers. We recommend the use of ```pyana``` over a personal python environment to allow for easier coordination between python and Offline, and easier sharing of scripts between users.

