#!/usr/bin/env python3

from myUtils import *
from config  import *

import socket
import sys
import os

import multiprocessing

usage_exit("path_to_alps", "vs_data_dir", "template_dir",  "log_dir")

for f in sys.argv[1:]:
    check_exist_err(f)

alps, data_dir, t_dir, log_dir = sys.argv[1:]


def worker(cmd):
    print ('>>>> running cmd: ', Green(cmd) )
    status = os.system(cmd)
    return (status, cmd)

def log_result(res):
    (status, cmd) = res
    if status != 0:
        print( '>>>>>> execution failed, status=', status, ', cmd=', Yellow(cmd) )
    else:
        print( '>>>>>> ', Green('Done: ' + cmd) )


pool = multiprocessing.Pool()


tasks = os.listdir(data_dir)

for name in tasks:
    bench = alps_config[andersen]

    fin = os.path.join(data_dir, name)
    check_exist_err(fin)

    fout = os.path.join(log_dir, name + ".log")

    bid = "%s -B " % alps
    bid += " -K %d " % bench[bidirect][maxK]

    tmpl_file = get_template(andersen)
    if tmpl_file is not None:
        tmpl = os.path.join(t_dir, tmpl_file)
        bid += " -T %s " % tmpl

    bid += " --bench %s " % name
    bid += " < %s " % fin
    bid += " > %s.bid " % fout

    pool.apply_async(worker, args = (bid,), callback = log_result)

pool.close()
pool.join()
