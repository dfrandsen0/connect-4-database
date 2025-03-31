#ifndef MCTS_H_
#define MCTS_H_

#include "node.h"

class MCTS {
public:
    static void startSimulation(Node* root, int numSims);
};

#endif
