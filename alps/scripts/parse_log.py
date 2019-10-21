#!/usr/bin/env python2

import sys

lines = []
with open(sys.argv[1]) as f:
    lines = f.readlines()

first_round = True
rounds = None
query_space = None
total_time = None
total_time = -1.0
refine_ct = 0
synth_programs = 0

for line in lines:
    if line.startswith("converged at round:"):
        rounds = int(line.strip()[20:])
    if line.startswith("overall_query_space:"):
        query_space = int(line.strip()[21:])
    if line.startswith("**ALPS_end_to_end takes"):
        total_time = int(line.strip()[24:-3])
    if first_round and line.find("total_votes: ") != -1:
        first_round = False
        refine_ct += int(line.strip()[13:])
    if line.find("refine_ct") != -1:
        parts = line.split(',')
        refine_ct += int(parts[1][13:])
    if line.startswith("remaining general programs:"):
        synth_programs += int(line.strip()[27:])
    if line.startswith("remaining specific programs:"):
        synth_programs += int(line.strip()[28:])

print "rounds: {}".format(rounds)
print "query space: {}".format(query_space)
print "synthesized programs: {}".format(synth_programs)
print "evaluated programs: {}".format(refine_ct)
print "total time: {}".format(total_time / 1000.)
