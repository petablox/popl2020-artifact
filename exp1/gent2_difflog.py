#!/usr/bin/env python3

import itertools
import os
import statistics
import sys

TIMEOUT = 3600

logFiles = os.listdir('./exp1-difflog')
benches = { fname[:fname.find('_')] for fname in logFiles }

with open('table2-difflog.csv', 'w') as outFile:
    print(f'BenchmarkName, RunningTime(seconds), EvalledProgs', file=outFile)
    print(f'BenchmarkName, RunningTime(seconds), EvalledProgs')
    for bench in sorted(benches):
        runTimes = []
        evalledProgs = []

        for fname in filter(lambda s: s.startswith(bench), logFiles):
            lines = [ line for line in open(f'./exp1-difflog/{fname}') ]

            timeLines = itertools.dropwhile(lambda s: not s.startswith('// Achieved loss'), lines)
            timeLines = list(filter(lambda s: s.startswith('Main:'), timeLines))
            assert(len(timeLines) <= 1)

            time = timeLines[0] if 0 < len(timeLines) else None
            time = time[len('Main: '):] if time else None
            time = time[:time.find(' ')] if time else None
            if time: runTimes.append(float(time))

            progs = [ line for line in lines if 'HybridAnnealingLearner.learn:52' in line or \
                                                'HybridAnnealingLearner.nextStateMCMC:110' in line ]
            evalledProgs.append(len(progs))

        medianTime = statistics.median(runTimes) if len(runTimes) > 0 else 'timeout'
        print(f'{bench}, {medianTime}, {statistics.median(evalledProgs)}', file=outFile)
        print(f'{bench}, {medianTime}, {statistics.median(evalledProgs)}')
