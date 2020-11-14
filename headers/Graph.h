#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>


class Graph {
public:
    Graph(std::vector<std::vector<int>> matrix);

    int size();

    int getMinVFNeighbor(int a) ;

    void infectNode(int nodeInd) ;

    bool isInfected(int nodeInd);

    bool isCarrier(int nodeInd);

    void removeEdges(int nodeInd);

    std::vector<std::vector<int>> getEdges();

    std::vector<bool> infectedVertex;
    std::vector<bool> carrierVertex;

private:
    std::vector<std::vector<int>> edges;

};

#endif
