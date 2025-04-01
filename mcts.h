#ifndef MCTS_H_
#define MCTS_H_

#include "node.h"

class MCTS {
private:
    static bool select(Node* root);
    static Node* expand(State* parentState, int move);
    static bool simulate(char** state, int move);
public:
    static void startSimulation(Node* root, int numSims);
};

#endif
