
import os
import sys
import pdb
import imp
import shutil
import pickle
import argparse


exist_color_module = None
try:
    imp.find_module('termcolor')
    exist_color_module = True
except ImportError:
    exist_color_module = False

if exist_color_module:
    from termcolor import colored, cprint
else:
    def colored(s, color, attrs = None):
        return s

def GreenBold(s):
    return colored(s,'green', attrs=['bold'])

def Green(s):
    return colored(s,'green')

def RedBold(s):
    return colored(s,'red', attrs=['bold'])

def Red(s):
    return colored(s,'red')

def YellowBold(s):
    return colored(s, 'yellow', attrs=['bold'])

def Yellow(s):
    return colored(s, 'yellow')

def install_pdb():
    def info(type, value, tb):
        if hasattr(sys, 'ps1') or not sys.stderr.isatty():
            # You are in interactive mode or don't have a tty-like
            # device, so call the default hook
            sys.__execthook__(type, value, tb)
        else:
            import traceback, pdb
             # You are not in interactive mode; print the exception
            traceback.print_exception(type, value, tb)
            print()
             # ... then star the debugger in post-mortem mode
            pdb.pm()
    sys.excepthook = info


def filter_files (instance_dir, s):
    return [f for f in os.listdir(instance_dir) if os.path.isfile(os.path.join(instance_dir, f)) and s in f ]


def check_exist_warn(f):
    if not os.path.exists(f):
        print ( YellowBold('Warn:'), " cannot find %sEnd" % Yellow(f) )
        return False
    return True

def check_exist_err(f):
    if not os.path.exists(f):
        print( RedBold('Error:'), " cannot find %sEnd" % Red(f) )
        raise Exception("error, cannot find file: %s" % f)

def usage_exit(*args):
    if len(sys.argv) != len(args) + 1:
        r = []
        r.append( Red("Usage:") )
        r.append( GreenBold(sys.argv[0]))
        r.extend( [ Green(x) for x in args ] )
        print( "\t".join(r) )
        exit()


def R(fpath):
    with open(fpath, "r") as fin:
        return fin.read().splitlines()


class UnionFind:
    def __init__(self, n):
        self.mark = range(n)

    def find (self,i):
        if i != self.mark[i]:
            self.mark[i] = self.find( self.mark[i] )
        return self.mark[i]

    def union(self,i,j):
        a = self.find(i)
        b = self.find(j)
        if a < b:
            self.mark[b] = a
        else:
            self.mark[a] = b

    def is_root(self,i):
        return i == self.mark[i]

    def get_roots(self):
        return [i for i,x in enumerate(self.mark) if i == x]
