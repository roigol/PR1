#ifndef TREE_H_
#define TREE_H_

#include <vector>
#include "Session.h"

class Session;
// TODO ASDASDSADASDASDSADAS
class Tree {
public:

    Tree(int rootLabel);

    void addChild(const Tree &child);

    static Tree *createTree(const Session &session, int rootLabel);

    virtual int traceTree() = 0;

    //added
//TODO DASD ASDASD
    virtual Tree *clone() const = 0;

    static Tree *BfsTreeMaker(Session &, int);

    Tree &getLeftChild() const;

    std::vector<Tree *> getChildren() const; // TODO Check  &getChildren why the & there.

    int getNode() const;

    bool hasChildren();

    int numOfChildren() const; // TODO MAYBE FOR LATER??

    int getRank() const;

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

    int traceTree2(Tree & currT, int cycle) ;

    int currCycle;
};

class MaxRankTree : public Tree {
public:

    MaxRankTree(int rootLabel);

    virtual int traceTree();

    //added

    virtual Tree *clone() const;

private:
    void traceTree2(Tree *currT, Tree *temp);
};

class RootTree : public Tree {
public:

    RootTree(int rootLabel);

    virtual int traceTree();

    //added

    virtual Tree *clone() const;
};

#endif
