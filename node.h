#ifndef NODE_H_
#define NODE_H_

#include "state.h"
#include "config.h"


class Node {
private:
    State* state = nullptr;
    int count = 0;
    int wins = 0;
    Node* children[NUM_CHILDREN];
public:
    Node();
    Node(State* state);

    State* getState();
    void setState(State* state);

    int getCount();
    void incCount();
    void setCount(int count);

    int getWins();
    void incWins();
    void setWins(int wins);

    Node** getChildren();
    Node* getChild(int index);
    void setChild(Node* child, int index);
};

#endif
