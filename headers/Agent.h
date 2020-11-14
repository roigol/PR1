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
    virtual Agent* clone() const =0 ;
    virtual void act(Session &session) = 0;

};

class ContactTracer : public Agent {
public:
    ContactTracer();
    Agent* clone() const;
    virtual void act(Session &session);
};


class Virus : public Agent {
public:
    int getNodeInd() ;

    Virus(int nodeInd) ;
    Agent* clone() const;

    virtual void act(Session &session);

private:
    const int nodeInd = 0;
};

#endif
