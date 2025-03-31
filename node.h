#ifndef NODE_H_
#define NODE_H_

#include "state.h"
#include "config.h"


class Node {
private:
    State* state = nullptr;
    int counts = 0;
    int wins = 0;
    Node* children[NUM_CHILDREN];
public:
    Node();
    Node(State* state);

    State* getState();
    void setState(State* state);

    int getCounts();
    void setCounts(int counts);

    int getWins();
    void setWins(int wins);

    Node** getChildren();
};


#endif
