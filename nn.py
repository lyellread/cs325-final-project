#!/usr/bin/env python3

import os, sys, math

def distance (a, b):
    return int(math.sqrt((a[1] - b[1])**2 + (a[2] - b[2])**2))


solution = []
nodes = []

with open(sys.argv[1], "r") as f:
    for l in f.readlines():
        node = []
        for x in l.lstrip().rstrip().split(" "):
            if len(x) == 0:
                continue
            node.append(int(x))
        nodes.append(node)


solution.append(nodes[0])
nodes.remove(nodes[0])

while nodes != []:

    current = solution[len(solution)-1]

    # find closest neighbor to current node
    nn = nodes[0]
    nd = 10000000000000000
    for node in nodes:
        if distance(node, current) < nd:
            nn = node
            nd = distance(node, current)

    # node now contains closest node.   
    solution.append(node)
    nodes.remove(node)

print(solution)

total_distance = 0
for x in range (0, len(solution)-1):
    total_distance += distance(solution[x], solution[x+1])
total_distance += distance(solution[0], solution[len(solution)-1])

print(total_distance)










