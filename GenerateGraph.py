from numpy import random, argsort, sqrt, ndarray
import math


def knn_search(query, data, k):
    data_n = data.shape[1]
    sqd = sqrt(((data - query[:, :data_n]) ** 2).sum(axis=0))
    idx = argsort(sqd)
    return idx[1:k + 1]


def generateGraph(vertexCount, minEedge):
    graph = dict()
    points = random.rand(2, vertexCount)
    for x in range(vertexCount):
        edge_num = math.floor(random.random() * 10) % 10 + \
            minEedge
        graph[x] = []
        query = ndarray(shape=(2, 1))
        query[0, 0] = points[0, x]
        query[1, 0] = points[1, x]
        nearest = knn_search(query, points, edge_num)
        for idx in nearest:
            graph[x].append((idx, random.random() * 10 % 5))
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
    vertexCount = 20
    passengersCount = 3
    graph = generateGraph(vertexCount, 4)
    passengers = generatePassenger(passengersCount, vertexCount)
    print graph
    print passengers
    writeFile("test.txt", graph, vertexCount,
              passengers, passengersCount)

if __name__ == '__main__':
    main()
