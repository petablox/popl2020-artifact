#!/usr/bin/env python3

from myUtils import *
from config  import *

import socket
import sys
import os

import multiprocessing

usage_exit("path_to_alps", "data_dir", "template_dir", "log_dir", "trials")

for f in sys.argv[1:-1]:
    check_exist_err(f)

alps, data_dir, t_dir, log_dir, trials = sys.argv[1:]

def worker(cmd):
    print ('>>>> running cmd: ', Green(cmd) )
    #status = 0
    status = os.system(cmd)
    return (status, cmd)

def log_result(res):
    (status, cmd) = res
    if status != 0:
        print( '>>>>>> execution failed, status=', status, ', cmd=', Yellow(cmd) )
    else:
        print( '>>>>>> ', Green('Done: ' + cmd) )


pool = multiprocessing.Pool()

#jobs = []

#tasks = SQL_bench
#tasks = [sql_16]
#tasks = KD_bench
#tasks = PA_simpl
#tasks = PA_complex
tasks = [openssl]
#tasks = [inflamation]
#tasks = [andersen]
#tasks = [downcast]
#tasks = [polysite]

for name in tasks:
    for i in range(int(trials)):
        bench = alps_config[name]

        tmpl_file = get_template(name)
        if tmpl_file is not None:
            tmpl = os.path.join(t_dir, tmpl_file)
        fin = os.path.join(data_dir, get_data(name))
        fout = os.path.join(log_dir, name + ".log")

        check_exist_err(fin)

        common_args = ""
        if get_template(name) is not None:
            common_args += " -T %s " % tmpl

        if staged in bench:
            common_args += " --augmentation={} ".format(bench[staged][0])
            common_args += " ".join(bench[staged][1])

        bid = "%s -B -R {}".format(i) % alps
        bid += " -K %d " % bench[bidirect][maxK]
        if maxM in bench[bidirect]:
            bid += " -M %d " % bench[bidirect][maxM]
        bid += common_args
        bid += " --bench %s " % name
        bid += " < %s " % fin
        bid += " > %s.bid " % fout


        #sta = "%s --staged " % alps
        #sta += common_args
        #sta += " --bench %s " % name
        #sta += " < %s " % fin
        #sta += " > %s.staged " % fout

        #jb_bid = multiprocessing.Process(target = worker, args=(bid,) )
        #jb_staged = multiprocessing.Process(target = worker, args=(sta,))
        #jobs.append(jb_bid)
        #jobs.append(jb_staged)

        pool.apply_async(worker, args = (bid,), callback = log_result)

pool.close()
pool.join()
