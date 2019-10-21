# Prosynth: Provenance-Guided Synthesis of Datalog Programs

## Obtaining Prosynth

### Prerequisites

1. Python 3
   1. Python 3 is commonly bundled with software distributions including Fedora and Homebrew.
   2. Ensure that the command `python3` works on your command line
2. Z3
   1. Z3 is also commonly bundled with software distributions including Fedora and Homebrew.
   2. One may also obtain Z3 from https://github.com/Z3Prover/z3.
   3. Ensure that the Python 3 interface to Z3 is compiled and installed. In particular, issue the following commands to
      the Python interpreter, `python3`:
      ```
      import z3
      solver = z3.Solver()
      solver.check()
      solver.model()
      ```
      If the import is successful, the Python interpreter will momentarily print the prompt for the next command.
      Otherwise, it will print an error message indicating failure to locate the appropriate libraries. The subsequently
      constructed solver object will report that it is satisfiable, and produce an empty model in response.
3. Souffle. Prosynth requires a small patch to be applied to Souffle. This patch is available in
   `prosynth/data/souffle.patch`. We will therefore clone and build Souffle ourselves. Ensure, however, that the
   prerequisites of Souffle are installed on your machine. Consult https://souffle-lang.github.io/build for further
   instructions.

### Installation

1. Clone the repository from https://github.com/petablox/prosynth.
2. Within the newly created `prosynth` directory, clone, patch, and build Souffle by running the command,
   `./scripts/clone.sh`.

## Running Prosynth on Benchmark Problems

1. Pick a problem instance from the set of benchmark problems in the `prosynth/benchmarks/curated` directory. Let the
   complete path of this directory be `PROBLEM_DIR`. We will explain the structure of this directory in the next
   section.
2. The first step to running Prosynth on a problem instance is to _prepare_ the problem. From the root `prosynth`
   directory, run the command `./scripts/prepare PROBLEM_DIR`. This command internally invokes Souffle to produce an
   optimized executable containing all candidate rules.
3. The next step is to actually perform _synthesis_. From the root `prosynth` directory, run the command
   `./scripts/prosynth PROBLEM_DIR 0 1`. For the `benchmarks/curated/scc` benchmark, the script should return in
   approximately 15--20 seconds on a contemporary laptop.

   In addition to the problem directory, the Prosynth script accepts two numerical Boolean-valued arguments. The first
   argument is a switch to enable coprovenance analysis, and the second argument is a switch to enable delta-debugging
   based why-not provenance. We recommend the use of the sequence of options, "`0 1`".

## Setting up New Problem Instances

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
   optimized executable. From the root Prosynth directory, as before, run `./scripts/prepare PROBLEM_DIR`. Note that
   this script only looks at the candidate rules and does not examine the training data.

## Undocumented Aspects of Prosynth

We plan to document the following aspects of the Prosynth distribution in the coming days.

1. Coprovenance: Generating annotated *_e.dl and *_en.dl files.
2. Automatic generation of large candidate rule sets.
