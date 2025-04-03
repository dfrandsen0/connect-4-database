#include <iostream>
#include <math.h>

#include "utility.h"
#include "state.h"
#include "node.h"
#include "mcts.h"
#include "play.h"

//later passed by argv?
#define NUM_SIMS	1000000

using namespace std;

int main(int argc, char* argv[]) {

    State* startingState = Utility::makeEmptyState();

    Node* root = new Node(startingState);

    MCTS::startSimulation(root, NUM_SIMS);

    cout << root->getCount() << " " << root->getWins() << endl;

    Node** children = root->getChildren();
    double lnParentCount = log(root->getCount());
    for(int i = 0; i < NUM_CHILDREN; i++) {
	cout << i << ": " << children[i]->getCount() << " " << children[i]->getWins() << "; " << Utility::calcUcb(children[i], lnParentCount) << endl;
    }

    return 0;
}

