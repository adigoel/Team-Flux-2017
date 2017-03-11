import numpy as np
from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt
import csv

def randrange(n, vmin, vmax):
    return (vmax-vmin)*np.random.rand(n) + vmin

masterDataList = []

with open('candata.csv', 'r') as f:
        reader = csv.reader(f)
        for row in reader:
                commitList = list(reader)
                masterDataList.append(commitList)


print(masterDataList[0][1][0])

#xs = latitude
#ys = longitude
#zs = altitude

fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
n = 100
for c, m, zl, zh in [('r', 'o', -50, -25), ('r', 'o', -30, -5)]:
    
    xs = [0,1,2,3,4]
    ys = [11,23,56,76,98]
    zs = [213,345,678,908,1909]

    ax.scatter(xs, ys, zs, c=c, marker=m)


for c, m, zl, zh in [('b', '^', -50, -25), ('b', '^', -30, -5)]:
    
    xs = [3,4,5,6,7]
    ys = [14,26,59,79,101]
    zs = [216,348,681,911,1912]

ax.set_xlabel('Latitude')
ax.set_ylabel('Longitude')
ax.set_zlabel('Altitude')

plt.show()


