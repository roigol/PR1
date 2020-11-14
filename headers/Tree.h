#ifndef TREE_H_
#define TREE_H_

#include <vector>
#include "Session.h"
class Session;

class Tree{
public:
    Tree(int rootLabel);
    void addChild(const Tree& child);

  //  static Tree* createTree(TreeType, int, int);
  static Tree * BfsTreeMaker (Session &, int );

    static Tree* createTree(const Session& session, int rootLabel);
    virtual int traceTree()=0;

protected:
    int node;
    std::vector<Tree*> children;
};

class CycleTree: public Tree{
public:
    CycleTree(int rootLabel, int currCycle);
    virtual int traceTree();

protected:
    int currCycle;
};

class MaxRankTree: public Tree{
public:
    MaxRankTree(int rootLabel);
    virtual int traceTree();
    int getRank();
private:
    int traceTree2(MaxRankTree * maxRT);
};

class RootTree: public Tree{
public:
    RootTree(int rootLabel);
    virtual int traceTree();

};

#endif
