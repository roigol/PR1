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

    // RULE OF FIVE:

    //destructor
    virtual ~Tree();

    //copy assignment operator
    Tree& operator=(const Tree& other);//TODO const???

    //Move Assignment Operator
    Tree& operator=(Tree &&other) noexcept;

    //copy constructor
    Tree (const Tree& other) ;

    //move constructor
    Tree(Tree&&) noexcept;

    void clear();

    virtual Tree *clone() const = 0;

    static Tree *BfsTreeMaker(Session &, int);

    Tree &getLeftChild() const;

    std::vector<Tree *> getChildren() const;

    int getNode() const;

    bool hasChildren();

    int getRank() const;

    int getRootLabel() const;


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

    int traceTree2(Tree* currT, int cycle) ;

    int currCycle;
};

class MaxRankTree : public Tree {
public:

    MaxRankTree(int rootLabel);

    virtual int traceTree();

    //added

    virtual Tree *clone() const;


private:
    Tree* traceTree2(Tree *currT, Tree *curr);
};

class RootTree : public Tree {
public:

    RootTree(int rootLabel);

    virtual int traceTree();

    //added

    virtual Tree *clone() const;
};

#endif
