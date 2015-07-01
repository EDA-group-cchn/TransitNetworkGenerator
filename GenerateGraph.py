from numpy import random, argsort, sqrt
import math


def knn_search(query, data, k):
    sqd = sqrt(((data - query) ** 2).sum(axis=0))
    idx = argsort(sqd)
    return idx[1:k + 1]


def generateGraph(vertexCount, minEdge):
    graph = dict()
    points = random.rand(2, vertexCount)
    for x in range(vertexCount):
        edge_num = math.floor(random.random() * 10) % 10 + \
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
    file.write(str(vertexCount) + "\n" + str(passengersCount) +
               "\n")
    for x in graph:
        for y in graph[x]:
            file.write(str(x) + " " + str(y[0]) + " " +
                       str(y[1]) + "\n")
    file.write("\n")
    for x in passengers:
        file.write(str(passengers[x][0]) + " " +
                   str(passengers[x][1]) + " " +
                   str(passengers[x][2]) + " " +
                   str(passengers[x][3]) + "\n")
    file.close()


def main():
    vertexCount = raw_input()
    passengersCount = raw_input()
    graph = generateGraph(vertexCount, 4)
    passengers = generatePassenger(passengersCount, vertexCount)
    writeFile("test.txt", graph, vertexCount,
              passengers, passengersCount)

if __name__ == '__main__':
    main()
