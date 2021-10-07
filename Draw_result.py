#!/usr/bin/python3
import matplotlib
matplotlib.use('Agg')
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.patches as mpatches
import os
import sys

Request = sys.argv[1]
Area = sys.argv[2]
ToDay = sys.argv[3]

Node_Scale = [100,200,300,400,500,600,700,800,900,1000]

plt.figure(figsize=(6,6))

DIR="result/" + str(ToDay) +"/"+str(Area)+"area/"+str(Request)+"requests/"

Result = []
for i in Node_Scale:
    fp = open(DIR + str(i) + "_" + str(Request) + ".txt")
    R_lines = fp.readlines()
    rows = len(R_lines)-1
    average = float(R_lines[rows].strip('\n'))
    average = int(average)
    Result.append(average)


plt.xlabel('Node Scale')
plt.ylabel('Throughput')
# Charging Scale => 1
lines = plt.plot(Node_Scale,Result,'bo')
plt.setp(lines, color='r', linewidth=2.0)
lines = plt.plot(Node_Scale,Result)
plt.setp(lines, color='r', linewidth=2.0)

# r_patch = mpatches.Patch(color='r', label='1 node')
# g_patch = mpatches.Patch(color='g', label='2 node')
# b_patch = mpatches.Patch(color='b', label='4 node')
# plt.legend(handles=[r_patch,g_patch,b_patch])

out_path = DIR+"/Result.png"
plt.savefig(out_path)
plt.close()