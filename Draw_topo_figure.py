#!/usr/bin/python3
import matplotlib
matplotlib.use('Agg')
import numpy as np
import matplotlib.pyplot as plt
import os
import sys
import networkx as nx

plt.figure(figsize=(20,10))

G=nx.Graph()
plt.subplot(1, 2, 1)  
fp = open("Node_Topolist.txt", "r")
lines = fp.readlines()
rows=len(lines)-1
nodes=np.zeros((rows,5))
row = 0
for x in range(1,rows+1):
    i = lines[x].strip().split('\t')
    nodes[row,:] = i[:]
    plt.scatter(nodes[row,1], nodes[row,2], s=5, c='red')
    G.add_node(int(nodes[row,0]))
    row+=1
fp.close()

fp = open("Edge_Topolist.txt", "r")
lines = fp.readlines()
rows=len(lines)-1
edges=np.zeros((rows,4))
row = 0
for x in range(1,rows+1):
    i = lines[x].strip().split('\t')
    edges[row,:] = i[:]
    # plt.scatter(links[row,1], links[row,2], s=1, c='red')
    G.add_edge(edges[row,1],edges[row,2])
    row+=1
fp.close()
plt.subplot(1, 2, 2)  
nx.draw(G, with_labels=True, font_weight='bold')
plt.savefig("topo_figure.png")