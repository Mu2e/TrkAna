# Logging In and Setting Up

## Objectives

In this exercise, you will learn how to:

* log in to a mu2egpvm machine, and
* how to set up your environment for this tutorial.

## Contents

* [Common Instructions](#Common-Instructions)
* [ROOT](#ROOT)
    * [ROOT Command Line](#ROOT-Command-Line)
    * [ROOT Macro](#ROOT-Macro)
* [Python](#Python)
    * [Python Command Line](#Python-Command-Line)
    * [Python Script](#Python-Script)
    * [Python Notebook](#Python-Notebook)

## Common Instructions

For all exercises, you should log in to a mu2egpvm machine like so:

```
ssh -XY username@mu2egpvm0X.fnal.gov
```

where ```username``` is your FNAL username, and ```mu2egpvm0X``` is between ```mu2egpvm01``` and ```mu2egpvm06```.

Once logged in, you should create a working area, move to it, and then setup a TrkAna [Musing](https://mu2ewiki.fnal.gov/wiki/Muse#Musings_.28published_muse_builds.29) like this:

```
mkdir your/new/working/area/
cd your/new/working/area/
setup mu2e
muse setup TrkAna v04_00_00
```

## ROOT

The ROOT exercises can be completed either on the command line or with a macro.

### ROOT Command Line

To use the ROOT command line, open up the ROOT prompt with:

```
root -l
```

You leave the command line by typing ```.q```

### ROOT Macro

To use a ROOT macro, open up a file in your favorite text editor. Assuming you name it ```Macro.C```, the file should contain:

```
void Macro() {
    // put your code in here
}
```

which can then be run on the command line with:

```
root -l Macro.C
```

## Python

The python exercises can be completed either on the command line, in a python notebook, or with a python script. 

For all of these, you will need to setup [pyana](https://mu2ewiki.fnal.gov/wiki/Pyana):

```
setup pyana v1_05_00
```

Pyana is a UPS package that provides a common python environment that all Mu2e analyzers can use. We recommend the use of pyana over a personal python environment to allow easier sharing of scripts between users.

### Python Command Line

To use the python command line, you can open it with:


```
python3
```

You leave the command line by pressing Ctrl+D.

### Python Script

To use a python script, open up a file in your favorite text editor. Assuming you name it ```Script.py```, which can then be run on the command line with:

```
python3 Script.py
```

### Python Notebook

If you want to use a python notebook for the python exercises, then you should log into to a mu2egpvm machine with a port forwarded:

```
ssh -XY -L YYYY:localhost:YYYY username@mu2egpvm0X.fnal.gov
```

where ```YYYY``` is a port number (e.g. 3000, 3001) that you will use to open a browser on your local machine.

Then you can start your notebook like this:

```
jupyter-notebook --no-browser --port=YYYY
```

and copy the URL that is printed, into your local browser.


Last Page: [Preliminary Information](prelims.md)

Next Page: [Opening and Inspecting a TrkAna ROOT file](opening.md)
