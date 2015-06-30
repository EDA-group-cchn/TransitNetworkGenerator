cmake_minimum_required(VERSION 3.0)
project(transit)

find_package(OpenMP REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++11 ${OpenMP_CXX_FLAGS}")

add_executable(transit main.cpp
               Passenger.cpp Passenger.h
               Graph.cpp Graph.h
               SubGraph.cpp SubGraph.h
               Route.cpp Route.h
               Gene.cpp Gene.h
               Random.cpp Random.h
               RoutesCache.h
               Chromosome.cpp Chromosome.h
               GeneticSolver.cpp GeneticSolver.h
               Dijkstra.cpp Dijkstra.h
               TSP.cpp TSP.h)

add_executable(graph_testing graph_testing.cpp
               Graph.cpp Graph.h
               SubGraph.cpp SubGraph.h
               Route.cpp Route.h
               Dijkstra.cpp Dijkstra.h)