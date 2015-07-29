#!/usr/bin/env python2

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
    colors = ['red', 'blue', 'green', 'black', 'blueviolet', 'aquamarine',
              'orange', 'yellow4', 'indigo', 'turquoise', 'violetred',
              'steelblue']
    for route, color in zip(graph_data, colors[:len(graph_data)]):
        for i in range(len(route)-1):
            graph.edge(route[i], route[i+1], color=color, penwidth="1.5")
    graph.format = 'png' #change format of output
    graph.render()


if __name__ == '__main__':
    main()
