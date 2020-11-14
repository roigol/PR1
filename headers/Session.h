#ifndef SESSION_H_
#define SESSION_H_

#include "fstream" // amit added
#include <queue>

#include <vector>
#include <string>
#include "Graph.h"
#include "Agent.h"
#include "Tree.h"
#include "json.hpp"
#include <iostream>

using namespace std;

class Agent;

enum TreeType {  // what does enum means???
    Cycle,
    MaxRank,
    Root
};

class Session {
public:
    Session(const std::string &path);

    void simulate();

    void addAgent(const Agent &agent);

    void setGraph(const Graph &graph);

    Graph *getGraph();

    void enqueueInfected(int);

    int dequeueInfected();

    //added

    TreeType getTreeType() const;

    void parseTreeType(string type);

    void parseAgents(const vector<tuple<string, int>> &agent);

    int getCurrCycle() const ;

private:
    Graph g;
    TreeType treeType;
    std::vector<Agent *> agents;

    //added

    int currCycle;
    std::queue<int> infectedQueue;
};

#endif
