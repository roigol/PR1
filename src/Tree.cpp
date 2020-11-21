
#include "../include/Tree.h"

//---------------------Tree--------------------------

Tree::Tree(int rootLabel) : node(rootLabel) {}




void Tree::addChild(const Tree &child) {
    children.push_back(child.clone());
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
                currTree->children.push_back(child);
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
    return !this->children.empty();
}

int Tree::getRank() const {
    return children.size();
}

vector<Tree *> Tree::getChildren() const {
    return children;
}

//destructor
Tree::~Tree() { clear(); }

void Tree::clear() {
    for (Tree *tree : children) {
        delete tree;
    }
}

//copy constructor
Tree::Tree(const Tree &other) : node(other.node), children({}) {
    for (auto i : other.children) {
        Tree *tree = i->clone();//TODO addChild()
        children.push_back(tree);
    }
}

// copy assignment operator
Tree &Tree::operator=(const Tree &other) {
    if (this != &other) {
        clear();
        node = other.node;
        for (Tree *tree: other.children) {
            addChild(*tree);//adds a clone;
        }
    }
    return *this;
}

// Move Constructor
Tree::Tree(Tree &&other) noexcept: node(other.node), children({}) {
    for (Tree *t : other.children) {
        this->children.push_back(t);
    }
    other.children.clear();
}

// Move Assignment Operator
Tree &Tree::operator=(Tree &&other) noexcept {
    if (this != &other) {
        clear();
        node = other.node;
        for (Tree *t : other.children) {
            this->children.push_back(t);
        }
        other.children.clear();
    }
    return *this;
}

int Tree::getRootLabel() const {  // TODO for the tester
    return node;
}

//---------------------CycleTree--------------------------

CycleTree::CycleTree(int rootLabel, int currCycle) : Tree(rootLabel), currCycle(currCycle) {

}

int CycleTree::traceTree() {
    return traceTree2(this, currCycle);
}


int CycleTree::traceTree2(Tree *currT, int cycle) {
    if (!currT->hasChildren() || cycle == 0)
        return currT->getNode();
    return traceTree2(currT->getChildren()[0], cycle - 1);
}


Tree *CycleTree::clone() const {
    return new CycleTree(node, currCycle);
}




//---------------------MaxRank--------------------------

MaxRankTree::MaxRankTree(int rootLabel) : Tree(rootLabel) {}

int MaxRankTree::traceTree() {
    Tree *maxRT = this;
    Tree *curr = this;
    maxRT = this->traceTree2(maxRT, curr);
    return maxRT->getNode();
}

Tree *MaxRankTree::traceTree2(Tree *maxRT, Tree *curr) {
    if (!curr->hasChildren())
        return maxRT;
    else {
        if (curr->getRank() > maxRT->getRank())
            maxRT = curr;
        for (Tree *elem : curr->getChildren()) {
            Tree *temp = traceTree2(maxRT, elem);
            if (temp->getRank() > maxRT->getRank()) {
                maxRT = temp;
            }
        }
        return maxRT;
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

