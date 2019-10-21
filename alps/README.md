# fse18-artifacts-183

ALPS is a tool for interactively synthesizing Datalog programs from templates and syntactic constraints.

## Setup

See the instructions in INSTALL, which we reproduce here:

Installation instructions:

1. (optional) build and install z3 (https://github.com/Z3Prover/z3), then update the z3 header and library paths (i.e. Z3_H, Z3_LIB) in Makefile accordingly. This is optional, because we already include a pre-built z3 located in the directory `z3_env`.

2. Set environmet variables by typing `. setenv`. 

3. To compile ALPS, please run `make`.

4. If the precompiled z3 does not work, build and install z3 as per step 1.
<!---
5. Before running ALPS, add the z3 dynamic library to LD_LIBRARY_PATH, e.g. `export LD_LIBRARY_PATH=$PATH_TO_ARTIFACT/z3_env/z3/bin`
-->

## Re-run main experiment

After compiling alps, our experiments should be runnable via (in the home directory of our project):

`scripts/run.py alps data/ data/templates [desired directory for logs]`

## Examine experimental logs

Our log files can be quite verbose. To extract key information from the log files (such as the number of rounds, number of possible queries, the number of evaluated programs, the number of
final candidate programs, and the total time, run the following:

`scripts/parse_log.py [location of log]`

## Other experiments

The data files used to generate Figure 2b) can be found at data/benchmarks/andersen_various_sizes.
To run experiment for Figure 2b): 

`scripts/run_andersen_vs.py  alps  data/benchmarks/andersen_various_sizes/  data/templates/ [directory for logs]`

The script used to collect data shown in Figure 2a) is `scripts/run_random_exp.py`. It is run similarly to scripts/run.py:

`scripts/run_random_exp.py alps data/ data/templates [number of trials] [desired directory for logs]`

The number of trials indicates the number of different random seeds (used for randomly selecting which tuple to query) to use.

## About some discrepancies 

There are a few discrepancies we uncovered when preparing this artifact.

- An `off-by-one` error when counting number of queries for some benchmarks. 
- A configuration error in the downcast benchmark. Now we have resolved the issue. 
- Due to a bug in Z3 SMT solver, the generated programs for the sql_8 benchmark are incorrect. We have reported this bug to the developers. (https://github.com/Z3Prover/z3/issues/1703)

However, these discrepancies do not change the general conclusion of our paper.

## Generating templates in our format (for future uses)

Meta-rules can be extracted from existing Datalog rules in the following manner.

`scripts/extract_templates [rule file]`

The rule file is expected to contain Datalog rules, e.g.

```
path(x,y) :- edge(x,y).
path(x,y) :- edge(x,z), path(z,y).
```

## License

ALPS uses the MIT License (see LICENSE)

