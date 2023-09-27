# TrkAna Tutorial

## Introduction

Welcome to the TrkAna Tutorial! 

The exercises in this tutorial are designed to be self-paced and for both ROOT and python analyzers.

If you have any questions, comments, or feedback, then you can either post on the [Mu2e Slack](https://mu2ewiki.fnal.gov/wiki/Slack) (either the ```#is_it_me_or_a_bug``` or ```#trkana``` channels), or [open a GitHub issue](https://github.com/Mu2e/TrkAna/issues)

## Contents

1. [Preliminary Information](pages/prelims.md): In this exercise, some preliminary information about TrkAna 

1. [Logging In and Setting Up](pages/setup.md): In these exercise, we will log in to the mu2egpvms and set up the environment for the rest of the exercises.

1. [Opening and Inspecting a TrkAna ROOT file](pages/opening.md): In this exercise, we will open and inspect the TrkAna ROOT files.

1. [Plotting Global Track Information](pages/n-hits.md): In this exercise, we will use the ```dem``` branch to plot the number of hits on a track.

The following are still work in progress...

1. [Plotting Local Track Information](pages/reco-mom.md): In this exercise, we will use the ```demfit``` branches to plot the reconstructed track momentum at the entrance of the tracker with and without various cuts.

1. [Plotting MC Truth Information of the Track](pages/mom-res.md): In this exercise, we will use the ```demmcvd``` branch compare reconstructed and MC turth information to plot the momentum resolution at the entrance of the tracker.

1. [Plotting MC Truth Information of the Particle](pages/e-loss.md): In this exercise, we will use the ```demmcsim``` branch to plot the energy of the particle when it was generated, and therefore the MC truth energy it lost. And also its starting position?

1. [Plotting MC Truth Information of Ancestor Particles](pages/genealogy.md): In this exercise, we will use the ```demmcsim``` branch to plot information of the particle's parent and grandparent

1. [Plotting the Simulated Energy Loss of Conversion Electrons in the Stopping Target and IPA](pages/tgt-ipa-e-loss.md)

1. [Plotting the Time Difference between a Track and CRV hit in the Extracted Position](pages/crv-extracted.md)

1. [Handling Large Datasets](pages/large-datasets.md)

Next Page: [Preliminary Information](pages/prelims.md)
