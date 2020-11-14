//
// Created by spl211 on 10/11/2020.
//

#include "../headers/Graph.h"




Graph::Graph(std::vector<std::vector<int>> matrix) : edges(matrix) {}

int Graph::getMinVFNeighbor(int a) {
    int min = -1;
    int counter = 0;
    bool found = false;
    while (!found) {
        if (!isInfected(edges[a][counter]) && !isCarrier(edges[a][counter])) {
            min = edges[a][counter];
            found = true;
        }
        counter++;
    }
    return min;
}

void Graph::infectNode(int nodeInd) {
    infectedVertex[nodeInd] = true;
}

bool Graph::isInfected(int nodeInd) {
    return (infectedVertex[nodeInd]);
}

bool Graph::isCarrier(int nodeInd) {
    return (carrierVertex[nodeInd]);
}

void Graph::removeEdges(int nodeInd) {
    for (int i = 0; i < edges[nodeInd].size(); i++) {
        if (edges[nodeInd][i] == 1) {
            edges[nodeInd][i] = 0;
            edges[i][nodeInd] = 0;
        }
    }
}

int Graph::size() {
    return edges.size();
}

std::vector<std::vector<int>> Graph::getEdges() {
    return edges;
}
