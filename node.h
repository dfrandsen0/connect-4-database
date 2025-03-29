#ifndef NODE_H_
#define NODE_H_

#include "state.h"


class Node {
private:
    State* state = nullptr;
    int counts = 0;
    int wins = 0;

public:
    Node();
    Node(State* state);
};


#endif
