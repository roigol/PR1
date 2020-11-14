//
// Created by spl211 on 10/11/2020.
//


#include "../headers/Session.h"


using json = nlohmann::json;
using namespace std;



Session::Session(const string &path) : g({}), currCycle(0), treeType(), agents(), infectedQueue() {
    ifstream i("path");
    json j;
    //j << i;
    i >> j;
    g = Graph(j["graph"]);
    treeType = parseTree(j["tree"]);
    agents = parseAgents(j["agents"]);

}

TreeType Session::parseTree(string type) { //check if needs to change to string& type
    if (type == "M")
        return MaxRank;
    if (type == "R")
        return Root;
    else
        return Cycle;
}

vector<Agent *> Session::parseAgents(const vector<tuple<string, int>> &agent) {
    for (auto i: agent) {
        if (get<0>(i) == "V") {
            agents.push_back(new Virus(get<1>(i)));
        } else
            agents.push_back(new ContactTracer());
    }

}


void Session::simulate() {}

void Session::addAgent(const Agent &agent) {
    agents.push_back(agent.clone());
}

void Session::setGraph(const Graph &graph) {}


void Session::enqueueInfected(int a) {
    infectedQueue.push(a);
}

int Session::dequeueInfected() {
    int i = -1;
    if (!infectedQueue.empty()) {
        i = infectedQueue.front();
        infectedQueue.pop();
    }
    return i;
}

TreeType Session::getTreeType() const {  // amit changed
    return treeType;  // should i write instead just "return treeType"?
}

Graph * Session::getGraph() { // amit changed
    return &g;
}


int Session::getCurrCycle() const{
    return currCycle;
}


//int size = agents.size();
//vector of new viruses



