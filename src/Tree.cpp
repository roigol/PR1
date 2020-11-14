//
// Created by spl211 on 10/11/2020.
//


#include "../headers/Tree.h"

//class Session;

//---------------------Tree--------------------------

Tree::Tree(int rootLabel) : node(rootLabel) {}

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
    std::queue<Tree *> queue;
    visited[node] = true;
    Tree *currTree = Tree::createTree(session, node);
    Tree *output = currTree;
    Tree *child;
    queue.push(currTree);
    while (!queue.empty()) {
        currTree = queue.front();
        queue.pop();
        for (int i = 0; i < g->size(); i++) {
            if (g->getEdges()[currTree->node][i] == 1 && !visited[i]) {//runs on node's neighbors
                visited[i] = true;
                child = Tree::createTree(session, i);
                currTree->addChild(*child);
                queue.push(child);
            }
        }
    }
    return output;
}

//---------------------CycleTree--------------------------

CycleTree::CycleTree(int rootLabel, int currCycle) : Tree(rootLabel), currCycle(currCycle) {

}

int CycleTree::traceTree() {
    CycleTree *curr = this;
    this->traceTree2(curr, 0);
    return curr->node;
}

void CycleTree::traceTree2(CycleTree *curr, int cycle) {
    if (curr->children.empty() | (curr->currCycle == cycle))
        return;
    else {
        curr = dynamic_cast<CycleTree *>(curr->children[0]);
        cycle++;
        traceTree2(curr, cycle);
    }
}

Tree *CycleTree::clone() const {
    return new CycleTree(node, currCycle);
}

//---------------------MaxRank--------------------------

MaxRankTree::MaxRankTree(int rootLabel) : Tree(rootLabel) {}


int MaxRankTree::traceTree() {
    MaxRankTree *maxRT = this;
    this->traceTree2(maxRT, this);
    return maxRT->node;
}

void MaxRankTree::traceTree2(MaxRankTree *maxRT, MaxRankTree *temp) {
    if (temp->children.empty())
        return;
    else {
        if (temp->getRank() > maxRT->getRank())
            maxRT = temp;
        for (auto & i : temp->children)
            this->traceTree2(maxRT, dynamic_cast<MaxRankTree *>(i));
    }
}

int MaxRankTree::getRank() const {
    return children.size();
}

Tree *MaxRankTree::clone() const {
    return new MaxRankTree(node);
}

//---------------------RootTree--------------------------

RootTree::RootTree(int rootLabel) : Tree(rootLabel) {}

int RootTree::traceTree() {
    return node;
}

Tree *RootTree::clone() const {
    return new RootTree(node);
}

