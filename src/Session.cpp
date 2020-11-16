
#include "../headers/Session.h"


using json = nlohmann::json;
using namespace std;


Session::Session(const string &path) : g({}), currCycle(0), treeType(), agents(), infectedQueue() {//TODO change order
    ifstream i("path");
    json j;
    //j << i;
    i >> j;
    g = Graph(j["graph"]);
    parseTreeType(j["tree"]);
    parseAgents(j["agents"]);

}

void Session::parseTreeType(string type) { //check if needs to change to string& type
    if (type == "M")
        treeType = MaxRank;
    else if (type == "R")
        treeType = Root;
    else
        treeType =  Cycle;
}

void Session::parseAgents(const vector<tuple<string, int>> &agent) {
    for (auto i: agent) {
        if (get<0>(i) == "V") {
            agents.push_back(new Virus(get<1>(i)));
            g.infectNode(get<1>(i));//TODO methods to add new viruses
        } else
            agents.push_back(new ContactTracer());
    }
}


void Session::simulate() {
    while(!g.done()){
        int size = agents.size();
        for(int i = 0; i < size; i++){
            agents[i]->act(*this);
        }
        currCycle++;
    }
}

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

TreeType Session::getTreeType() const {
    return treeType;
}

Graph *Session::getGraph()  { //cons??
    return &g;
}


int Session::getCurrCycle() const {
    return currCycle;
}



