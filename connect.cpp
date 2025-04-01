#include <iostream>
#include <math.h>

#include "utility.h"
#include "state.h"
#include "node.h"
#include "mcts.h"

//later passed by argv?
#define NUM_SIMS	100

using namespace std;

int main(int argc, char* argv[]) {

    State* startingState = Utility::makeEmptyState();

    Node* root = new Node(startingState);

    MCTS::startSimulation(root, NUM_SIMS);

    return 0;
}
