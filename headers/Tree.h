#ifndef TREE_H_
#define TREE_H_

#include <vector>
#include "Session.h"

class Session;

class Tree {
public:
    Tree(int rootLabel);

    void addChild(const Tree &child);

    static Tree *createTree(const Session &session, int rootLabel);

    virtual int traceTree() = 0;

    //added

    virtual Tree *clone() const = 0 ;

    static Tree *BfsTreeMaker(Session &, int);

protected:
    int node;
    std::vector<Tree *> children;
};

class CycleTree : public Tree {
public:
    CycleTree(int rootLabel, int currCycle);

    virtual int traceTree();

    //added

    virtual Tree *clone() const;

private:
    void traceTree2(CycleTree *, int);

    int currCycle;
};

class MaxRankTree : public Tree {
public:
    MaxRankTree(int rootLabel);

    virtual int traceTree();

    //added

    int getRank() const;

    virtual Tree *clone() const;

private:
    void traceTree2(MaxRankTree * , MaxRankTree *);
};

class RootTree : public Tree {
public:
    RootTree(int rootLabel);

    virtual int traceTree();

    //added

    virtual Tree *clone() const;
};

#endif
