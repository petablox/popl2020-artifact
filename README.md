Provenance-Guided Synthesis of Datalog Programs
===============================================

Mukund Raghothaman; Jonathan Mendelson; David Zhao; Mayur Naik; Bernhard Scholz

Introduction
------------

This is the artifact package accompanying our POPL 2020 submission titled _Provenance-Guided Synthesis of Datalog
Programs_. The paper presents a new algorithm to synthesize Datalog programs from input-output examples. We have
implemented this algorithm in a tool named ProSynth, and benchmarked them against the existing solvers, ALPS and
Difflog.

The paper is accessible from https://r-mukund.github.io/pdf/2019-Prosynth.pdf. The paper reviews may be found at
https://www.dropbox.com/s/pk5qunsrcbe51ip/reviews.txt, and our response and supplementary data are available at
https://www.dropbox.com/s/cnephfo5d9drtxs/rebuttal.txt and https://www.dropbox.com/s/82gyotioahgrm6p/rebuttal-app.pdf
respectively.

This artifact contains all three tools (ProSynth, ALPS, and Difflog), benchmark files, and scripts to reproduce the
experiments described in the paper. In this document, we will describe the outline of these experiments, how to run
them, and also describe how one may use ProSynth to solve Datalog synthesis problems of their own.

Installing the Artifact
-----------------------

The recommended way to install this artifact is by using Docker:
```
git clone https://github.com/petablox/popl2020-artifact.git
cd popl2020-artifact/scripts/docker
[sudo] docker build -t prosynth .
[sudo] docker run -it prosynth /bin/bash
```

Structure of the Experiments
----------------------------

In our paper, we present a method of computing why-not provenance using delta debugging. Depending on whether this is
switched on or off, ProSynth can be run in two different modes, named `nprov-S` and `nprov-Delta` respectively.
Subsequently, all results presented in the paper arise out of two experiments:

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

The broad trends in our experiments should be reproducible on most contemporary desktop and laptop workstations.
However, because we repeatedly run scripts to capture variations in running times, they can take some time to completely
reproduce. It is therefore helpful to have a multicore CPU to run these tasks in parallel and make the experiments
finish quickly. Let NUM_CORES be the number of parallel cores on the computer:
```
export NUM_CORES=6 # (for example)
```

Experiment 1 requires us to run all three tools, ProSynth, ALPS and Difflog. Execute the following sub-tasks:
```
./exp1/prosynth.sh $NUM_CORES
./exp1/alps.sh
./exp1/difflog.sh $NUM_CORES
```

Reproducing Experiment 2
------------------------

Running ProSynth on New Problems
--------------------------------
