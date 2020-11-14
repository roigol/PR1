//
// Created by spl211 on 10/11/2020.
//


#include "../headers/Agent.h"


Agent::Agent() {}

ContactTracer::ContactTracer() {}

Agent *ContactTracer::clone() const {
    return new ContactTracer();
}

void ContactTracer::act(Session &session) {
    int infectedN = session.dequeueInfected();
    if (infectedN != -1) {
        Tree * tree =  Tree::BfsTreeMaker(session, infectedN);
        int toRemove = tree->traceTree();
        session.getGraph()->removeEdges(toRemove);
    }
}

Virus::Virus(int nodeInd) : nodeInd(nodeInd) {}

Agent *Virus::clone() const {
    return new Virus(nodeInd);
}

int Virus::getNodeInd() {
    return nodeInd;
}


void Virus::act(Session &session) {
    Graph *g = session.getGraph();
    if (g->infectedVertex[nodeInd]) {
        int minN = g->getMinVFNeighbor(nodeInd);
        session.addAgent(Virus(minN));
        g->carrierVertex[minN] = true;
    } else {
        g->infectNode(nodeInd);
        session.enqueueInfected(nodeInd);
    }
}

