#ifndef MCTS_H_
#define MCTS_H_

#include "node.h"

class MCTS {
private:
    static bool select(Node* root, int playerNum, double cValue);
    static Node* expand(State* parentState, int move, int playerNum);
    static bool simulate(State* parentState, int move, int playerNum);
public:
    static void startSimulation(Node* root, int numSims, double cValue);
};

#endif
