#!/usr/bin/env python2

from numpy import random, argsort, sqrt
from sys import argv
import math


def knn_search(query, data, k):
    sqd = sqrt(((data - query) ** 2).sum(axis=0))
    idx = argsort(sqd)
    return idx[1:k + 1]


def generateGraph(vertexCount, minEdge):
    graph = dict()
    points = random.rand(2, vertexCount)
    for x in range(vertexCount):
        edge_num = int(random.random() * 10) % 10 + \
            minEdge
        graph[x] = []
        query = points[:, x:x + 1]
        nearest = knn_search(query, points, edge_num)
        for idx in nearest:
            graph[x].append((idx, random.random() * 10))
    return graph


def generatePassenger(passengerCount, vertexCount):
    passengers = dict()
    for x in range(passengerCount):
        f = int(math.floor(random.random() * 100) % vertexCount)
        t = int(math.floor(random.random() * 100) % vertexCount)
        while (t == f):
            t = int(math.floor(random.random() * 100) % vertexCount)
        passengers[x] = [f, t, random.random() * 10,
                         random.random() * 10]
    return passengers


def writeFile(filename, graph, vertexCount, passengers, passengersCount):
    file = open(filename, 'wb')
    edgeCount = 0
    for x in graph:
        edgeCount += len(graph[x])
    file.write("%d %d %d\n" % (vertexCount, edgeCount, passengersCount))
    for x in graph:
        for y in graph[x]:
            file.write("%d %d %f\n" % (x, y[0], y[1]))
    file.write("\n")
    for x in passengers:
        file.write("%d %d %f %f\n" % tuple(passengers[x]))
    file.close()


def main():
    vertexCount = int(argv[1])
    passengersCount = int(argv[2])
    graph = generateGraph(vertexCount, 4)
    passengers = generatePassenger(passengersCount, vertexCount)
    writeFile("test.txt", graph, vertexCount,
              passengers, passengersCount)

if __name__ == '__main__':
    main()
