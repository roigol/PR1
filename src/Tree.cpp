//
// Created by spl211 on 10/11/2020.
//


#include "../headers/Tree.h"

class Session;


Tree::Tree(int rootLabel): node(rootLabel) {}

void Tree::addChild(const Tree &child) {}


Tree *Tree::createTree(const Session &session, int rootLabel) {
    Tree *t;
    TreeType type = session.getTreeType();
    switch (type) {
        case Root: {
            t = new RootTree(rootLabel);
            break;
        }
        case MaxRank: {
            t = new MaxRankTree(rootLabel);
            break;
        }
        case Cycle: {
            t = new CycleTree(rootLabel, session.getCurrCycle());
            break;
        }
        default: {
            break;
        }
    }
    return t;
}


Tree *Tree::BfsTreeMaker(Session &session, int node) {
    Graph *g = session.getGraph();
    bool visited[g->size()];
    for (int i = 0; i < g->size(); i++)//init visited
        visited[i] = false;
    std::vector<Tree *> queue;
    visited[node] = true;
    Tree *root = Tree::createTree(session, node);
    Tree *output = root;
    Tree *temp;
    queue.push_back(root);
    while (!queue.empty()) {
        for (int i = 0; i < g->size(); i++) {
            if (g->getEdges()[node][i] == 1 && !visited[i]) {//runs on node's neighbors
                visited[i] = true;
                temp = Tree::createTree(session, node);
                root->addChild(*temp);
                queue.push_back(temp);
            }
        }
    }
    return output;
}


CycleTree::CycleTree(int rootLabel, int currCycle) : Tree(rootLabel), currCycle(currCycle) {

}

int CycleTree::traceTree() {}


MaxRankTree::MaxRankTree(int rootLabel) : Tree(rootLabel) {}


int MaxRankTree::traceTree() {
    MaxRankTree *maxRT = this;
    this->traceTree2(maxRT);
    return maxRT->node;
}

int MaxRankTree::traceTree2(MaxRankTree *maxRT) {
    if (children.size() == 0)
        return 0;
    else {
        if (children.size() > maxRT->getRank())
            maxRT = this;//???????????????????????????????????
        for (int i = 0; i < this->getRank(); i++)
            this->traceTree2(dynamic_cast<MaxRankTree *>(children[i]));
    }
}

int MaxRankTree::getRank() {
    return children.size();
}

RootTree::RootTree(int rootLabel) : Tree(rootLabel) {}

int RootTree::traceTree() {
    return node;
}

