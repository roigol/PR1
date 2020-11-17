#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
//include "Session.h"

class Graph {
public:
    Graph(std::vector<std::vector<int>> matrix);

    void infectNode(int nodeInd);

    bool isInfected(int nodeInd);

    //added

    int size();

    int NodeToInfect(int a);

    bool isCarrier(int nodeInd);

    void removeEdges(int nodeInd);

    static bool done();

    std::vector<std::vector<int>> getEdges();

    std::vector<bool> getInfectedNodes();

    std::vector<bool> getCarrierNodes();

private:
    std::vector<bool> infectedNodes;
    std::vector<bool> carrierNodes;
    std::vector<std::vector<int>> edges;
};

#endif
