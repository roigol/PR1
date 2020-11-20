//
// Created by spl211 on 10/11/2020.
//

#include "../headers/Graph.h"

#include <utility>


Graph::Graph(std::vector<std::vector<int>> matrix) : edges(std::move(matrix)), numOfCarrierNodes(0) {
    infectedNodes.assign(edges.size(), false);
    carrierNodes.assign(edges.size(), false);
}

int Graph::NodeToInfect(int a) {
    for (int i = 0 ;i < edges.size() ;i++) {
        if (edges[a][i]== 1 && !isInfected(i) && !isCarrier(i)) {
            return i;
        }
    }
    return -1;
}

void Graph::infectNode(int nodeInd) {
    infectedNodes[nodeInd] = true;
}

bool Graph::isInfected(int nodeInd) {
    return (infectedNodes[nodeInd]);
}

bool Graph::isCarrier(int nodeInd) {
    return (carrierNodes[nodeInd]);
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

bool Graph::done() const {
    return numOfCarrierNodes == 0;
}

std::vector<bool> &Graph::getInfectedNodes() {
    return infectedNodes;
}

std::vector<bool> &Graph::getCarrierNodes() {
    return carrierNodes;
}

void Graph::increaseNumOfCarrierNodes() {
    numOfCarrierNodes++;
}

void Graph::decreaseNumOfCarrierNodes() {
    numOfCarrierNodes--;
}

void Graph::setNumOfCarrierNodes() {
    numOfCarrierNodes = 0;
}
