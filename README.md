Provenance-Guided Synthesis of Datalog Programs
===============================================

Mukund Raghothaman; Jonathan Mendelson; David Zhao; Mayur Naik; Bernhard Scholz

Introduction
------------

This is the artifact package accompanying our POPL 2020 submission titled _Provenance-Guided Synthesis of Datalog
Programs_. The paper presents a new algorithm to synthesize Datalog programs from input-output examples. We have
implemented this algorithm in a tool named ProSynth, and benchmarked them against the existing solvers, ALPS and
Difflog.

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
[sudo] docker run -it prosynth
```
When started, the container is already running an SSH daemon, with the root password set to `abc123`. Therefore, one may
run the following command instead of the last one:
```
[sudo] docker run -it -p 2200:22 prosynth
```
and connect to the container via SSH connections:
```
ssh -p 2200 root@localhost
root@localhost's password: abc123
```
The argument `-p 2200:22` binds port 2200 of the host machine to port 22 of the container. This mode of operation is
useful if one wishes to transfer data between the container and host, such as with `ssh` and `scp`.

To uninstall the artifact, run the following commands:
```
[sudo] docker images           # To list the currently installed images
[sudo] docker rmi prosynth     # To delete the prosynth image
[sudo] docker images           # To verify successful deletion
```

__Hardware Requirements.__ We ran the experiments on a Xeon 6154 CPU running at 3 GHz with 18 cores and 36 threads. The
system was equipped with 394 GB of RAM, and was running the Ubuntu 18.04 LTS operating system over the Linux kernel
version 4.15. The container image was composed using Docker version 19.04. While the artifact is small, running the
experiments produces a large volume of logs. We require the machine to have at least 30 GB of free space for the logs.

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
cd /popl2020-artifact
./exp1/prosynth.sh $NUM_CORES
./exp1/alps.sh
./exp1/difflog.sh $NUM_CORES
./exp1/plot_f6_b.py
```
Note that with `NUM_CORES=6`, and running on a 3.1GHz Core i9-9900 CPU, the first command takes approximately 4 hours to
complete.

The data from the first script, `./exp1/prosynth.sh` is stored in a sub-directory named `/popl2020-artifact/exp1-work`.
This includes detailed logs from each run of ProSynth, and a summary file named `/popl2020-artifact/exp1-work/data.log`.
After all runs are complete, it is processed to produce:
1. the ProSynth-specific columns of Table 2 in `table2-prosynth.csv`,
2. the non-normalized version of Figure 6b,
3. Table 3 and Figure 8 of the main paper, and
4. Figure 2 in the supplementary data we provided to reviewers.

The second script stores its data in a subdirectory named `exp1-alps`, and records the ALPS-specific columns of Table 2
in a file named `table2-alps.csv`. The third script stores its data in a subdirectory named `exp1-difflog`, and produces
the files `table2-difflog.csv` and `f6_a.pdf`, and the final script produces Figure 6b.

We note that the maximum and minimum measured values (such as the ends of the whiskers in the plots and the last two
columns of Table 3) vary significantly across runs. Aggregate values, such as the median values, are less susceptible to
variations of this form.

Reproducing Experiment 2
------------------------

As before, fix the number of cores available in the CPU:
```
export NUM_CORES=6 # (for example,)
```
and run:
```
./exp2/run.sh $NUM_CORES
```
After a while, the script produces Figure 7 (and `f7_t.pdf` showing running time instead of number of Z3 calls), and
Figure 1 from the supplementary data provided to reviewers.

### Notes

1. As before, we note that the ends of the whiskers can vary significantly between runs as they record the extreme
   values of a set of random variables. Measures of central tendency, such as the median represented by the orange line,
   exhibits a much more robust and stable trend across experimental runs.

2. Because of an error in the way the experiment was set up, the Y-axis in Figure 1 from the supplementary data is an
  order-of-magnitude smaller than reported, but our central claim, that the running time of ProSynth grows modestly with
  the number of candidate rules, continues to hold.

A Brief Tutorial to Using ProSynth
----------------------------------

### Running ProSynth on Individual Benchmark Problems

1. Pick a problem instance from the set of benchmark problems in the `/popl2020-artifact/benchmarks/regular` directory.
   Let the complete path of this directory be `PROBLEM_DIR`. We will explain the structure of this directory in the next
   subsection.
2. The first step to running Prosynth on a problem instance is to _prepare_ the problem. From the root `prosynth`
   directory, run the command `./scripts/prepare $PROBLEM_DIR`. This command internally invokes Souffle to produce an
   optimized executable containing all candidate rules.
3. The next step is to actually perform _synthesis_. From inside the main `/popl2020-artifact` directory, run the
   command `./prosynth/scripts/prosynth $PROBLEM_DIR 0 1 data.log`. For the `benchmarks/regular/scc` benchmark, the
   script should return in 15--20 seconds on a contemporary laptop.

   In addition to the problem directory, the Prosynth script accepts two numerical Boolean-valued arguments. The first
   argument is a switch to enable coprovenance analysis, and the second argument is a switch to enable delta-debugging
   based why-not provenance. We recommend the use of the sequence of options, "`0 1`". The final argument is the name of
   the file in which to dump some summary statistics.

### Setting up New Problem Instances

1. There are four ingredients in a Prosynth problem instance:
   1. Names and signatures of input, ouput, and invented relations.
   2. Set of candidate rules of which the target program forms a subset.
   3. Set of tuples inhabiting the input relations and expected to inhabit the output relations.

2. Placing the training data:
   1. For each input relation `Rin`, place the set of tuples in the training data in a file named `Rin.facts`.
   2. For each output relation `Rout`, place the set of expected output tuples in a file named `Rout.facts`.

3. Create a file named `rules.small.dl` using any of the existing benchmarks as a template.

   1. We allow our Datalog rules to have a simple model of types: every relation is associated with a list of types
      called its _signature_, and the fields of every tuple inhabiting this relation match the corresponding type.
      Declare all relevant types at the beginning of the `rules.small.dl` file.

      For example, in the case of SCC, we are modeling properties of graphs, which consist of vertices. At the beginning
      of `rules.small.dl`, we therefore find a line saying `.type V`, indicating the type of vertices.

   2. Declare all input, output, and invented relations in the problem instance. Each declaration consists of two lines,
      the first specifying the relation's signature, and the second identifying whether it is _consumed_ by the Datalog
      program (i.e., whether it is an input relation), or _produced_ by the Datalog program (i.e., whether it is an
      output or an invented relation).

      For SCC, this looks as follows:
      ```
      .decl Edge(v0: V, v1: V)
      .input Edge
      .decl inv(v0: V, v1: V)
      .output inv
      .decl SCC(v0: V, v1: V)
      .output SCC
      ```

   3. Declare a reserved input relation named `Rule`. This permits a mechnism by which Prosynth enables or disables
      various combinations of rules and thereby discovers the target program.
      ```
      .decl Rule(n: number)
      .input Rule
      ```

   4. Create a set of well-typed candidate rules, one on each line. Associate each rule with a unique number `n`, and
      add a literal `Rule(n)` to the rule body. We will call this number the _name_ of the rule.

4. List the names of all candidate rules in a file named `ruleNames.small.txt`.

5. One subsequently _prepares_ the problem instance by running Souffle on the `rules.small.dl` file to produce an
   optimized executable. From the main `/popl2020-artifact` directory, as before, run
   `./prosynth/scripts/prepare $PROBLEM_DIR`. Note that this script only looks at the candidate rules and does not
   examine the training data.

6. Now you are ready to do _synthesis_. Run `./prosynth/scripts/prosynth $PROBLEM_DIR 0 1 data.log`. If synthesis is
   successful, the script will print the set of rules that form the target program.
