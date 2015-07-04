from graphviz import Digraph
from sys import argv


def getGraphData(filename):
    routes = []
    with open(filename, 'r') as file:
        for x in file:
            routes.append(x.strip().split(' '))
    return routes


def main():
    filename = argv[1]
    graph_data = getGraphData(filename)
    graph = Digraph()
    for route in graph_data:
        for i in range(len(route)-1):
            graph.edge(route[i], route[i+1], color="red")
    graph.format = 'png' #change format of output
    graph.render()


if __name__ == '__main__':
    main()
