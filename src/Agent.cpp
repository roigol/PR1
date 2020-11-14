//
// Created by spl211 on 10/11/2020.
//


#include "../headers/Agent.h"

//---------------------Agent--------------------------
Agent::Agent() = default;

Agent::~Agent() = default;

//---------------------CT--------------------------

ContactTracer::ContactTracer() = default;

Agent *ContactTracer::clone() const {
    return new ContactTracer();
}

void ContactTracer::act(Session &session) {
    int infectedN = session.dequeueInfected();
    if (infectedN != -1) {
        Tree *infectedTree = Tree::BfsTreeMaker(session, infectedN);
        int toRemove = infectedTree->traceTree();
        session.getGraph()->removeEdges(toRemove);
        // delete infectedTree;//TODO
    }
}

//---------------------Virus--------------------------

Virus::Virus(int nodeInd) : nodeInd(nodeInd) {}

Agent *Virus::clone() const {
    return new Virus(nodeInd);
}

int Virus::getNodeInd() const {
    return nodeInd;
}

void Virus::act(Session &session) {
    Graph *g = session.getGraph();
    if (g->getInfectedNodes()[nodeInd]) {
        int minN = g->NodeToInfect(nodeInd);
        session.addAgent(Virus(minN));
        g->getCarrierNodes()[minN] = true;
    } else {
        g->infectNode(nodeInd);
        session.enqueueInfected(nodeInd);
    }
}
