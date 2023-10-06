# Logging In and Setting Up

## Objectives

In this exercise, you will:

* set up your environment on a mu2egpvm machine to complete the exercises with either ROOT or python

## Contents

* [Common Instructions](#Common-Instructions)
    * [Logging In](#Logging-In)
    * [Creating Your Work Area](#Creating-Your-Work-Area)
    * [Getting the List of TrkAna Files](#Getting-the-List-of-TrkAna-Files)
* [ROOT](#ROOT)
    * [ROOT Command Line](#ROOT-Command-Line)
    * [ROOT Macro](#ROOT-Macro)
* [Python](#Python)
    * [Python Command Line](#Python-Command-Line)
    * [Python Script](#Python-Script)
    * [Python Notebook](#Python-Notebook)

## Common Instructions

### Logging In

For all exercises, you should log in to a mu2egpvm machine like so:

```
ssh -XY username@mu2egpvm0X.fnal.gov
```

where ```username``` is your FNAL username, and ```mu2egpvm0X``` is between ```mu2egpvm01``` and ```mu2egpvm06```.

### Creating Your Work Area

Once logged in, you should create a working area following the instructions [here](https://mu2ewiki.fnal.gov/wiki/LoginTutorial#app_disk), move to it, and then setup a TrkAna [Musing](https://mu2ewiki.fnal.gov/wiki/Muse#Musings_.28published_muse_builds.29) like this:

```
mkdir your/new/working/area/
cd your/new/working/area/
setup mu2e
muse setup TrkAna v04_01_00
```

### Getting the List of TrkAna Files

We will use a TrkAna dataset that has already been created by Production: ```nts.mu2e.CeEndpointMix1BBSignal.MDC2020z1_best_v1_1_std_v04_01_00.tka``` (see the [preliminary information](prelims.md#Simulation-Samples) for a breakdown of that the dataset name means.

We can get a list of official TrkAna datasets with the following command:

```
setup mu2efiletools
mu2eDatasetList --tier=nts --owner=mu2e --format=tka
```

You should see the dataset ```nts.mu2e.CeEndpointMix1BBSignal.MDC2020z1_best_v1_1_std_v04_01_00.tka``` in that list.

Now we can get the list of files in this dataset like this:

```
setup dhtools
samListLocations --defname=nts.mu2e.CeEndpointMix1BBSignal.MDC2020z1_best_v1_1_std_v04_01_00.tka
```

and you will see a list of files printed to the terminal output. You will notice that these all have ```tape``` in the directory. These files are on tape and nominally need to be copied to disk to be used in our jobs. Usually if these files have been used recently, then they will be on disk and you don't need to [prestage](https://mu2ewiki.fnal.gov/wiki/Prestage) them (which can take a while).

For these exercises, we will just use whichever files are already on disk and we won't worry about analyzing the whole dataset. To get the list of files that are already on disk, we can use the ```-d``` option of ```samListLocations``` (note that the ```sam``` part of this command refers to [SAM](https://mu2ewiki.fnal.gov/wiki/SAM). We will also write a filelist for use later:

```
mkdir filelists
setup dhtools
samListLocations -d --defname=nts.mu2e.CeEndpointMix1BBSignal.MDC2020z1_best_v1_1_std_v04_01_00.tka > filelists/nts.mu2e.CeEndpointMix1BBSignal.MDC2020z1_best_v1_1_std_v04_01_00.list
```

## ROOT

The ROOT exercises can be completed either on the command line or with a macro.

### ROOT Command Line

To use the ROOT command line, open up the ROOT prompt with:

```
root -l
```

and type in the commands from the exercises.

You exit the command line type ```.q```

### ROOT Macro

To use a ROOT macro, open up a file in your favorite text editor. Assuming you name it ```Macro.C```, the file should contain:

```
void Macro() {
    // put the commands from the exercises here
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

and type in the commands from the exercises.

You exit the command line by pressing Ctrl+D.

### Python Script

To use a python script, open up a file in your favorite text editor and type in the commands in the exercises. Assuming you name it ```Script.py```, which can then be run on the command line with:

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

and copy the URL that is printed, into your local browser. You then type commands into each cell and presst Ctrl+Enter to execute the commands in that cell.


Last Page: [Preliminary Information](prelims.md)

Next Page: [Opening and Inspecting a TrkAna ROOT file](opening.md)
