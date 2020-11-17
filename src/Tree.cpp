
#include "../headers/Tree.h"
// TODO SADASDASDASDASDSADADS
//---------------------Tree--------------------------

Tree::Tree(int rootLabel) : node(rootLabel) {}


//TODO copy constructor:

void Tree::addChild(const Tree &child) {
    children.push_back(child.clone());  //TODO check.
}


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


Tree *Tree::BfsTreeMaker(Session &session, int node) {// session should be const?
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

Tree &Tree::getLeftChild() const {
    return *children[0];
}

int Tree::getNode() const {  // check for const
    return this->node;
}

bool Tree::hasChildren() {
    return this->children.empty();
}

int Tree::numOfChildren() const {
    return children.size();
}

int Tree::getRank() const {
    return children.size();
}

vector<Tree *> Tree::getChildren() const {
    return children;
}

Tree::~Tree() { clear(); }

void Tree::clear() {
    for (Tree *tree : children) {
        if (tree != nullptr) {
            delete tree;
            tree = nullptr;
        }
        children.clear();
    }
}

//TODO copy constructor
Tree::Tree(const Tree &other) : node(other.node), children({}) {
       for (int i = 0; i < children.size(); i++) {
           Tree *tree = other.children[i]->clone();
           children.push_back(tree);
       }
}

// copy assignment operator
const Tree &Tree::operator=(const Tree &other) { // TODO check return type
    if (this != &other) {
        clear();
        node = other.node;
        for (Tree *tree: children) {
            addChild(*tree);
        }
    }
    return *this;
}



//---------------------CycleTree--------------------------

CycleTree::CycleTree(int rootLabel, int currCycle) : Tree(rootLabel), currCycle(currCycle) {

}

int CycleTree::traceTree() {
    return traceTree2(*this, currCycle);
} // Amit fixed and by adding 2 methods - hasChildren and getLeftChild.


int CycleTree::traceTree2(Tree &currT, int cycle) {// TODO check if should change to * instead of &.
    if (!currT.hasChildren() || cycle == 0)
        return currT.getNode();
    else
        traceTree2(currT.getLeftChild(), cycle - 1);

}


Tree *CycleTree::clone() const {
    return new CycleTree(node, currCycle);
}




//---------------------MaxRank--------------------------

MaxRankTree::MaxRankTree(int rootLabel) : Tree(rootLabel) {}

int MaxRankTree::traceTree() {
    MaxRankTree *maxRT = this;
    MaxRankTree *temp = this;
    this->traceTree2(maxRT->clone(), temp->clone());
    return maxRT->getNode();
}

void MaxRankTree::traceTree2(Tree *maxRT, Tree *temp) {
    if (!temp->hasChildren())
        return;
    else {
        if (temp->getRank() > maxRT->getRank())
            maxRT = temp->clone();
        for (auto &i : temp->getChildren())
            this->traceTree2(maxRT, i->clone());
    }
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

