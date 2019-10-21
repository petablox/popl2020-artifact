#!/usr/bin/env python3

import hypertools as hyp
import logging
import matplotlib.pyplot as plt
import numpy as np
import sys

logging.basicConfig(level=logging.INFO, \
                    format="[%(asctime)s] %(levelname)s [%(name)s.%(funcName)s:%(lineno)d] %(message)s", \
                    datefmt="%H:%M:%S")

########################################################################################################################
# 1. Read Input

# 1a. Command line parameters

positionPattern = sys.argv[1]
logFileNames = sys.argv[2:]

# 1b. Parse log files

def parseLogFile(fname):
    logging.info('Parsing {}'.format(fname))
    lines = [ line for line in open(fname) if positionPattern in line ]
    if not lines: logging.warning('No position vectors found in file {}'.format(fname))
    lines = [ line[line.find(positionPattern):] for line in lines ]
    lines = [ line[len(positionPattern):] for line in lines ]
    lines = [ list(map(float, line.split(', '))) for line in lines ]
    losses = np.array([ [ line[0] ] for line in lines ])
    positions = np.array([ line[1:] for line in lines ])
    return { 'name': fname, 'losses': losses, 'positions': positions }

logs = [ parseLogFile(fname) for fname in logFileNames ]

########################################################################################################################
# 2. Reduce dimensions

# We want to apply the same transformation to all points. So:

# 2a. Combine points into single list, and reduce

combinedPositions = np.concatenate([ log['positions'] for log in logs ])
combinedPositionsReduced = hyp.reduce(combinedPositions, ndims=2, reduce='PCA')

# 2b. Separate combined points

separatedPositions = []
for log in logs:
    losses = log['losses']
    positionsReduced = combinedPositionsReduced[:len(log['positions'])]
    combinedPositionsReduced = combinedPositionsReduced[len(log['positions']):]

    spa = np.concatenate((positionsReduced, losses), axis=1)
    logging.info(spa.shape)
    separatedPositions.append({ 'name': log['name'], 'prl': spa })

# 2c. Only keep large log files, and only after they stabilize

large = 200
separatedPositions = [ sp for sp in separatedPositions if len(sp['prl']) > large ]
def stabilize(sp):
    name = sp['name']
    prl = sp['prl']
    return { 'name': name, 'prl': prl[large:] }
separatedPositions = [ stabilize(sp) for sp in separatedPositions ]
logging.info('Preserved {} traces'.format(len(separatedPositions)))

########################################################################################################################
# 3. Draw scatter plot

fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
for reducedLog in separatedPositions:
    # ax.scatter(reducedLog['prl'][:, 0], reducedLog['prl'][:, 1], reducedLog['prl'][:, 2])
    ax.plot(reducedLog['prl'][:, 0], reducedLog['prl'][:, 1], reducedLog['prl'][:, 2])
ax.set_xlabel('X')
ax.set_ylabel('Y')
ax.set_zlabel('Loss')
plt.show()
