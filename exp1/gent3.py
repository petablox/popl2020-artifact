#!/usr/bin/env python3

import os
import sys
import subprocess
import numpy as np

print("Done running experiments!")
print("Generating tables and figures...")

prosynth_running_time = dict()
prosynth_running_time_no_delta = dict()
alps_running_time = dict()
difflog_running_time = dict()
prosynth_program_count_z3 = dict()
prosynth_program_count_souffle = dict()
alps_program_count = dict()
difflog_program_count = dict()

f = open("exp1-work/data.log", "r")
for line in f:
	benchmark_name = line[line.find("name: '")+7:line.find("',")]
	benchmark_name = benchmark_name[benchmark_name.find("/")+1:]
	benchmark_name = benchmark_name[benchmark_name.find("/")+1:benchmark_name.rfind("/")]

	program_count_z3 = line[line.find("z3:")+3:]
	program_count_z3 = int(program_count_z3[:program_count_z3.find(",")])

	program_count_souffle = line[line.find("souffle:")+8:]
	program_count_souffle = int(program_count_souffle[:program_count_souffle.find(",")])

	running_time = line[line.find("runtime:")+8:]
	running_time = float(running_time[:running_time.find(",")])

	setting_delta = line[line.find("setting_delta:")+15:]
	setting_delta = setting_delta[:setting_delta.find("}")]

	if setting_delta == "0":
		if not benchmark_name in prosynth_running_time_no_delta:
			prosynth_running_time_no_delta[benchmark_name] = set()
		prosynth_running_time_no_delta[benchmark_name].add(running_time)
	else:
		if not benchmark_name in prosynth_program_count_z3:
			prosynth_program_count_z3[benchmark_name] = set()
		prosynth_program_count_z3[benchmark_name].add(program_count_z3)

		if not benchmark_name in prosynth_program_count_souffle:
			prosynth_program_count_souffle[benchmark_name] = set()
		prosynth_program_count_souffle[benchmark_name].add(program_count_souffle)

		if not benchmark_name in prosynth_running_time:
			prosynth_running_time[benchmark_name] = set()
		prosynth_running_time[benchmark_name].add(running_time)

with open('table3.csv', 'w') as f_t3:
	print("Benchmark Name, Prosynth No Delta Median Run Time, Prosynth Delta Median Run Time, Prosynth No Delta Maximum Run Time, Prosynth Delta Maximum Run Time\n", file=f_t3)
	for benchmark_name in prosynth_running_time:
		f_t3.write(benchmark_name +',')
		f_t3.write(str(np.median(list(prosynth_running_time_no_delta[benchmark_name]))) + ",")
		f_t3.write(str(np.median(list(prosynth_running_time[benchmark_name]))) + ",")
		f_t3.write(str(np.amax(list(prosynth_running_time_no_delta[benchmark_name]))) + ",")
		f_t3.write(str(np.amax(list(prosynth_running_time[benchmark_name]))))
		f_t3.write("\n")










