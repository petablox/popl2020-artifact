Provenance-Guided Synthesis of Datalog Programs
===============================================

Mukund Raghothaman; Jonathan Mendelson; David Zhao; Bernhard Scholz; Mayur Naik

Introduction
------------

This is the artifact package accompanying our POPL 2020 submission titled _Provenance-Guided Synthesis of Datalog
Programs_. The paper presents a new algorithm to synthesize Datalog programs from input-output examples. We have
implemented this algorithm in a tool named ProSynth, and benchmarked them against the existing solvers, ALPS and
Difflog.

This artifact contains all three tools (ProSynth, ALPS, and Difflog), benchmark files, and scripts to reproduce the
experiments described in the paper. In this document, we will describe the outline of these experiments, how to run
them, and also describe how one may use ProSynth to solve Datalog synthesis problems of their own.

Hardware and Estimated Time for Reproduction
--------------------------------------------

__TODO:__ How long do the experiments take to reproduce?

__TODO:__ Explain the `tsp -S` command

We conducted our experiments on a server with an 18-core Xeon 6154 CPU clocked at 3 GHz and with 394 GB of RAM. However,
we only used the multiple cores to simultaneously run multiple experiments and iterate quickly. Furthermore, all
benchmarks are CPU-bound rather than memory-bound. We expect similar results to be obtained on workstations and laptops
with more modest memory resources.

Structure of the Experiments
----------------------------

In our experiments, we run ProSynth in two different modes, named `nprov-S` and `nprov-Delta` respectively. We will
explain these modes in more detail later in this documentation.

All results presented in the paper arise out of two experiments:

1. __Experiment 1:__ Run ProSynth (in both modes), ALPS, and Difflog on all benchmarks, with the standard set of
   candidate rules. ProSynth (in both modes) and Difflog are each run 32 times to capture variance in running times.

   The data from this experiment is used to produce __Tables 2 and 3__, and __Figures 6 and 8__ in the main paper. The
   data is also used to produce __Figure 2__ in the supplementary data provided as part of our response to the
   reviewers.

2. __Experiment 2:__ Run ProSynth (in `nprov-Delta` mode) on the `scc` and `1-object-1-type` benchmarks. Here, we vary
   the size of the set of candidate rules, and measure its effect on the time needed to synthesize the program. Each
   experiment is repeated 8 times to capture variance in running times.

   The data from this experiment is used to produce __Figure 7__ in the main paper, and __Figure 1__ in the
   supplementary data provided to the reviewers.

Reproducing Experiment 1
------------------------

Reproducing Experiment 2
------------------------

Running ProSynth on New Problems
--------------------------------


