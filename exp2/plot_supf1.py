#!/usr/bin/env python3

import numpy as np

import matplotlib
matplotlib.use("TkAgg")
matplotlib.rcParams['pdf.fonttype'] = 42

import matplotlib.pyplot as plt
import matplotlib.pylab as pylab
import matplotlib.patches as mpatches
from matplotlib.legend_handler import HandlerLine2D


import sys
import os
import pickle

ops = ["min","avg","box","median"]
if len(sys.argv) != 2 or (sys.argv[1] not in ops):
    print("usage: ", sys.argv[0], "option(i.e. min,median,avg,box)")
    exit()
option = sys.argv[1]

andersen = "andersen"

data = [["andersen", ]]
stats = {}

#('andersen', 'NaiveEvaluator', 1, 63.79036713, [9.50282142, 9.229187106, 8.507771925, 8.389737418, 7.456736622, 7.412505975, 6.255905456, 6.214917931, 0.049403028, 0.040989799])
prosynth_running_time = dict()
prosynth_running_time_no_delta = dict()
alps_running_time = dict()
difflog_running_time = dict()
prosynth_program_count_z3 = dict()
prosynth_scale_program_count_z3 = dict()
prosynth_program_count_souffle = dict()
alps_program_count = dict()
difflog_program_count = dict()

f = open("exp2-work/data.log", "r")
for line in f:
    benchmark_name = line[line.find("name: '")+7:line.find("',")]
    benchmark_type = benchmark_name[benchmark_name.find("/")+1:benchmark_name.rfind("/")]
    benchmark_name = benchmark_name[benchmark_name.rfind("/")+1:benchmark_name.find("|")]

    program_count_z3 = line[line.find("z3:")+3:]
    program_count_z3 = int(program_count_z3[:program_count_z3.find(",")])

    program_count_souffle = line[line.find("souffle:")+8:]
    program_count_souffle = int(program_count_souffle[:program_count_souffle.find(",")])

    running_time = line[line.find("runtime:")+8:]
    running_time = float(running_time[:running_time.find(",")])

    setting_delta = line[line.find("setting_delta:")+15:]
    setting_delta = setting_delta[:setting_delta.find("}")]

    if benchmark_type == "benchmarks":
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
    else:
        if setting_delta == "1":
            if not benchmark_name in prosynth_scale_program_count_z3:
                prosynth_scale_program_count_z3[benchmark_name] = set()
            prosynth_scale_program_count_z3[benchmark_name].add(program_count_z3)

            if not benchmark_name in prosynth_running_time:
                prosynth_running_time[benchmark_name] = set()
            prosynth_running_time[benchmark_name].add(running_time)

f.close()

andersen_stats = dict()
sizes = list()
for benchmark_name in prosynth_running_time:
    if benchmark_name[:benchmark_name.find("_")] == "1-object-1-type":
        andersen_stats[benchmark_name] = list(prosynth_running_time[benchmark_name])
        sizes.append(benchmark_name)

#sizes = [x*100 for x in range(1, 11)]
#sizes.append(100)

andersen_performance = None
box_data = None
if option == "median":
    andersen_performance = [ np.median(np.array(andersen_stats[x])) for x in sizes ]
elif option == "min":
    andersen_performance = [ np.min(np.array(andersen_stats[x])) for x in sizes ]
elif option == "avg":
    andersen_performance = [ np.mean(np.array(andersen_stats[x])) for x in sizes ]
elif option == "box":
    box_data = [ andersen_stats[x] for x in sizes  ]
else:
    print("unknown option:", option)
    exit()

assert (box_data is None) or (andersen_performance is None)

fig, ax = plt.subplots()

xs = range(1, 11)
if box_data:
    bp = ax.boxplot (box_data, whis='range')
    # alps_result = [148, 147, 178, 267, 284, 311, 315, 319, 334, 375]
    # alps_result = [x/60. for x in alps_result]
    # alps_result_plot, = ax.plot( ax.get_xticks(), alps_result, 'og')
if andersen_performance:
    ax.plot(xs,  andersen_performance, 'go' )

#ax.set_xlim([0,43])
#ax.set_ylim([0,60])

ticksize=12
#plt.yticks([14,15,16,17, 18])
x_tick_labels = [s[s.find("_")+1:-1] for s in sizes]

xss = [i for i in range(1, len(x_tick_labels)+1)]
plt.xticks(xss, x_tick_labels)
ax.tick_params(labelsize=ticksize)


# adjust the ratio of axis
x1,x2,y1,y2 = plt.axis()
ylength = y2 - y1
xlength = x2 - x1
aspect_ratio = 0.55
aspect = float(xlength)/ylength * aspect_ratio
ax.set_aspect(aspect)

#xlabel = "Number of templates"
#ylabel = "Running time (min)"
ylabel = "Running Time"
#ylabel = "Avg. evaluation time (sec)"

xlabel = "Number of Candidate Rules"
ax.set_ylabel(ylabel, fontsize=15)#, fontweight='bold')
ax.set_xlabel(xlabel, fontsize=11)

x_low, x_high = ax.get_xlim()
_, ylim = ax.get_ylim()
#ax.text( 0.5 * (x_low + x_high)  , 1.04 * ylim, 'time (second)', ha='center', va='center')


#print "get_xticks: ", ax.get_xticks()

def autolabel():
    # attach some text labels
    xticks = ax.get_xticks()
    N = len(xticks)
    _, ylim = ax.get_ylim()
    print
    for i in xrange(N):
        x = xticks[i]
        percent = questions[i] * 100.0 / overall_Qs[i]
        height = questions[i]
        if percent > 0.01:
            s1 = "%.1lf%%" % percent
        else:
            s1 = "%.3f%%" % percent
        s2 = "%ds" % overall_tms[i]

        #ax.text(x, 0.1 +  ylim, s2, ha='center', va='bottom')
        ax.text(x, 0.15 + height, s2, ha='center', va='bottom', fontsize=9)
        ax.text(x, -0.10 +  height, s1, ha='center', va='top', fontsize=9)


#autolabel()

fig.tight_layout()

plt.savefig('supf1.pdf')#, bbox_inches='tight')

#plt.show()
