% Provenance-Guided Synthesis of Datalog Programs
% Mukund Raghothaman; Jonathan Mendelson; David Zhao; Bernhard Scholz; Mayur Naik

Introduction
============

This is the artifact package accompanying our POPL 2020 submission titled _Provenance-Guided Synthesis of Datalog
Programs_. The paper presents a new algorithm to synthesize Datalog programs from input-output examples. We have
implemented this algorithm in a tool named [ProSynth]{.smallcaps}, and benchmarked them against the existing solvers,
[ALPS]{.smallcaps} and [Difflog]{.smallcaps}.

This artifact contains all three tools---[ProSynth]{.smallcaps}, [ALPS]{.smallcaps}, and [Difflog]{.smallcaps}---and
scripts to reproduce the experiments described in the paper. In this document, we will describe the outline of these
experiments, how to run them, and also how one may use [ProSynth]{.smallcaps} to solve Datalog synthesis problems.

Outline of the Experiments
==========================

The [ProSynth]{.smallcaps} tool can be run in two different modes, `p‾r‾o‾v‾-S`

All results presented in the paper arise out of two experiments:

1. sdf
