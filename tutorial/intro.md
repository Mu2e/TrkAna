# TrkAna Tutorial

## Introduction

Welcome to the TrkAna Tutorial! These exercises are designed to be self-paced and pick-and-choose. Both ROOT- and python-based examples are shown.

## TrkAna Tree Structure

TrkAna is a ROOT TTree with one "candidate" track per row. A candidate track is the type of the track that is the being analyzed (e.g. downstream e-minus).

The columns of the ROOT TTree include fit information about the candidate track, as well as any "supplemental" tracks that the analysis needs. For example, in the standard TrkAna trees upstream e-minus and downstream mu-minus are supplemental tracks since a muon-to-electron conversion search will need to veto on upstream tracks, and ensure that the reconstructed particle is an electron and not a muon.

## Exercises

1. [Opening and Inspecting a TrkAna ROOT file](opening.md)

1. [Reconstructed Track Momentum](reco-mom.md)

In this exercise you will plot the reconstructed momentum of simulated conversion electrons.
