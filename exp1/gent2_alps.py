#!/usr/bin/env python3

import sys
import os

convert_set = dict()
convert_set["dev_set_005"] = "sql_01"
convert_set["dev_set_017"] = "sql_02"
convert_set["dev_set_048"] = "sql_03"
convert_set["recent_posts_001"] = "sql_04"
convert_set["textbook_5_2_1"] = "sql_05"
convert_set["recent_posts_014"] = "sql_06"
convert_set["recent_posts_042"] = "sql_07"
convert_set["top_rated_posts_032"] = "sql_08"
convert_set["dev_set_010"] = "sql_09"
convert_set["dev_set_062"] = "sql_10"
convert_set["textbook_5_1_1"] = "sql_11"
convert_set["textbook_5_2_9"] = "sql_12"
convert_set["recent_posts_003"] = "sql_13"
convert_set["dev_set_018"] = "sql_14"
convert_set["textbook_5_1_4X"] = "sql_15"

f_t2 = open("table2-alps.csv", "w")
f_t2.write("Benchmark Name, ALPS Run Time, ALPS Number Evaluated Programs\n")
for filename in os.listdir(sys.argv[1]):
    print(filename)
    if filename.endswith(".log.bid"):
        benchmark_name = filename[:filename.find(".log.bid")]
        if benchmark_name in convert_set:
            benchmark_name = convert_set[benchmark_name]
        first_round = True
        rounds = None
        query_space = None
        total_time = None
        refine_ct = 0
        synth_programs = 0
        f = open(os.path.join(sys.argv[1], filename), "r")
        for line in f:
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
        f.close()
        if total_time is not None: print(f'{benchmark_name}, {total_time / 1000.}, {refine_ct}', file=f_t2)
        else: print(f'{benchmark_name}, timeout, timeout', file=f_t2)
        
f_t2.close()
