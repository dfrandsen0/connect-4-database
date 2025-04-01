#include <iostream>
#include <climits>
#include <math.h>

#include "mcts.h"
#include "node.h"
#include "utility.h"

using namespace std;

void MCTS::startSimulation(Node* root, int numSims) {
    for(int i = 0; i < numSims; i++) {
	MCTS::select(root);
    }
}

// how to handle getting to the end of the tree?
bool MCTS::select(Node* root) {
    Node** rootKids = root->getChildren();
    bool* available = root->getState()->getAvailable();

    for(int i = 0; i < NUM_CHILDREN; i++) {
	if(available[i] && rootKids[i] == nullptr) {
	    rootKids[i] = MCTS::expand(root->getState(), i);
	    int win = simulate(rootKids[i]->getState()->copyState(), i);
	    //increase counts
	    return true; //res of simulate
	}
    }

    int maxValue = INT_MIN;
    int index = -1;

    double lnParentCount = log(root->getCount());
    double temp;

    for(int i = 0; i < NUM_CHILDREN; i++) {
	if(available[i]) {
	    temp = Utility::calcUcb(rootKids[i], lnParentCount);
	    if(temp > maxValue) {
		maxValue = temp;
		index = i;
	    }
	}
    }

    root->incCount();
    if(MCTS::select(rootKids[index])) {
	root->incWins();
	return true;
    } else {
	return false;
    }
}

Node* MCTS::expand(State* parentState, int move) {
    int nextPlayerNum = 1;
    if(parentState->getPlayerNum() == 1) {
	nextPlayerNum = 2;
    }

    char** stateCopy = parentState->copyState();

    for(int i = 0; i < NUM_ROWS; i++) {
	if(stateCopy[move][i] == 0) {
	    stateCopy[move][i] = parentState->getPlayerNum();
	    break;
	}
    }

    State* newState = new State(nextPlayerNum, stateCopy);
    Node* newNode = new Node(newState);

    return newNode;
}

bool MCTS::simulate(char** state, int move) {
    

    return true;
}






