#ifndef AGENT_H_
#define AGENT_H_

#include <vector>
#include "Session.h"//roi added
#include "Graph.h"//roi added
#include "Tree.h"

class Session;

class Agent {
public:
    Agent();

    virtual void act(Session &session) = 0;

// added:

    virtual Agent *clone() const = 0;
};

class ContactTracer : public Agent {
public:
    ContactTracer();

    virtual Agent *clone() const;

    virtual void act(Session &session);
};


class Virus : public Agent {
public:
    int getNodeInd() const;

    Virus(int nodeInd);

    virtual Agent *clone() const;

    virtual void act(Session &session);

private:
    const int nodeInd = 0;// TODO =0??

};

#endif
