# TrkAna Tutorial

## Introduction

Welcome to the TrkAna Tutorial! 

The exercises in this tutorial are designed to be self-paced and for both ROOT and python analyzers.

If you have any questions, comments, or feedback, then you can either post on the ```#trkana``` channel of the [Mu2e Slack](https://mu2ewiki.fnal.gov/wiki/Slack), or [open a GitHub issue](https://github.com/Mu2e/TrkAna/issues)

### Other useful links:

* explanation of branches and leaves [spreadsheet](https://docs.google.com/spreadsheets/d/1IMZVgj74vxGTWqAFRtFEEcYChujJyc38VcopZh52jhc/edit)
    * one tab for each major branch
* version istory of TrkAna is on the [Mu2eWiki](https://mu2ewiki.fnal.gov/wiki/TrkAna#Version_History_.2F_TrkAna_Musings)

## Contents

1. [Preliminary Information](pages/prelims.md): In this exercise, we will get some preliminary information about TrkAna.

1. [Logging In and Setting Up](pages/setup.md): In this exercise, we will log in to the mu2egpvms and set up the environment for the rest of the exercises.

1. [Opening and Inspecting a TrkAna ROOT file](pages/opening.md): In this exercise, we will open and inspect the TrkAna ROOT files.

1. [Plotting Global Track Information](pages/n-hits.md): In this exercise, we will use the ```dem``` branch to plot the number of hits on a track. We will also apply an event-level cut on the number of dem tracks.

1. [Plotting Local Track Information](pages/reco-mom.md): In this exercise, we will use the ```demfit``` branches to plot the reconstructed track momentum at the entrance of the tracker with and without a time cut.

1. [Plotting MC Truth Information of the Track](pages/mom-res.md): In this exercise, we will use the ```demmcvd``` branch to compare reconstructed and MC truth information to plot the momentum resolution at the entrance of the tracker.

Note that the tutorials below still need to be updated for version 5 TrkAna trees:

1. [Plotting MC Truth Information of the Particle](pages/start-pos.md): In this exercise, we will use the ```demmcsim``` branch to plot the starting position of the conversion electrons.

1. [Plotting MC Truth Information of Ancestor Particles](pages/genealogy.md): In this exercise, we will use the ```demmcsim``` branch to plot the starting position of the muons that generate conversion electrons, and the starting positions of decay-in-orbit electrons.

Incomplete tutorials that have something useful:

1. [Plotting the Time Difference between a Track and CRV hit in the Extracted Position](pages/crv-extracted.md): In this exercise, we will use the ```crvinfo``` branch to plot the time difference between a track and CRV hit in the extracted position. 

Future tutorials:

1. [Plotting the Simulated Energy Loss of Conversion Electrons in the Stopping Target and IPA](pages/tgt-ipa-e-loss.md): In this exercise, we will use the ```demmcsic_stoppingtarget``` and ```demmcsic_protonabsorber``` branches to plot the MC true energy loss of conversion electrons in the stopping target and inner proton absorber.

1. [Making Your Own TrkAna Tree](pages/make-your-own.md): In this exercise, we will make our own TrkAna tree that has a different structure to the default.

Next Page: [Preliminary Information](pages/prelims.md)
