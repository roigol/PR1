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

    // RULE OF FIVE
    virtual ~Tree();

    Tree& operator=(const Tree& other);

    Tree& operator=(Tree &&other) noexcept;

    Tree (const Tree&) ;

    Tree(Tree&&) noexcept;

    void clear();

    virtual Tree *clone() const = 0;

    static Tree *BfsTreeMaker(Session &, int);

    Tree &getLeftChild() const;

    std::vector<Tree *> getChildren() const; // TODO Check  &getChildren why the & there.

    int getNode() const;

    bool hasChildren();

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
