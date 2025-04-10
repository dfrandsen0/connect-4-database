
#include <iostream>
#include <climits>
#include <math.h>
#include <cstring>

#include "mcts.h"
#include "node.h"
#include "utility.h"
#include "play.h"

using namespace std;

void printState(char** state);

void MCTS::startSimulation(Node* root, int numSims, double cValue) {
    for(int i = 0; i < numSims; i++) {
	MCTS::select(root, root->getState()->getPlayerNum(), cValue);
    }
}

// how to handle getting to the end of the tree?
bool MCTS::select(Node* root, int playerNum, double cValue) {
    Node** rootKids = root->getChildren();
    bool* available = root->getState()->getAvailable();

    if(root->getFinished() != NodeFinished::UNFINISHED) {
	root->incCount();
	if(root->getFinished() == NodeFinished::WIN) {
	    root->incWins();
	    return true;
	} else {
	    //TODO : ADD DRAW
//	    root->incWins();
	    return false;
	}
    }

    for(int i = 0; i < NUM_CHILDREN; i++) {
	if(available[i] && rootKids[i] == nullptr) {
	    rootKids[i] = MCTS::expand(root->getState(), i, playerNum);

	    int win = false;
	    if(rootKids[i]->getFinished() == NodeFinished::UNFINISHED) {
		win = simulate(rootKids[i]->getState(), i, playerNum);
	    } else if(rootKids[i]->getFinished() == NodeFinished::WIN) {
		win = true;
	    }

	    rootKids[i]->incCount();
	    root->incCount();
	    if(win) {
		rootKids[i]->incWins();
		root->incWins();
	    }
	    return win;
	}
    }

    double maxValue = INT_MIN;
    int index = -1;

    double lnParentCount = log(root->getCount());
    double temp;

    for(int i = 0; i < NUM_CHILDREN; i++) {
	if(available[i]) {
	    temp = Utility::calcUcb(rootKids[i], lnParentCount, cValue);
	    if(temp > maxValue) {
		maxValue = temp;
		index = i;
	    }
	}
    }


    if(MCTS::select(rootKids[index], playerNum, cValue)) {
	root->incCount();
	root->incWins();
	return true;
    } else {
	root->incCount();
	return false;
    }
}

Node* MCTS::expand(State* parentState, int move, int playerNum) {
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

    if(Play::checkWin(stateCopy, parentState->getPlayerNum())) {
	if(parentState->getPlayerNum() == playerNum) {
	    newNode->setFinished(NodeFinished::WIN);
	} else {
	    newNode->setFinished(NodeFinished::LOSE);
	}
    } else {
	for(int i = 0; i < NUM_COLUMNS; i++) {
	    if(stateCopy[i][NUM_ROWS - 1] == 0) {
		return newNode;
	    }
	}
	newNode->setFinished(NodeFinished::LOSE);
    }

    return newNode;
}

bool MCTS::simulate(State* parentState, int move, int playerNum) {
    char** state = parentState->copyState();

    int nextSpots[NUM_COLUMNS];
    fill(nextSpots, nextSpots + NUM_COLUMNS, 6);
    for(int i = 0; i < NUM_COLUMNS; i++) {
	for(int j = 0; j < NUM_ROWS; j++) {
	    if(state[i][j] == 0) {
		nextSpots[i] = j;
		break;
	    }
	}
    }

    int spots[NUM_COLUMNS];
    fill(spots, spots + NUM_COLUMNS, -1);
    int s = 0;

    int allSpots = 0;
    for(int i = 0; i < NUM_COLUMNS; i++) {
	if(nextSpots[i] < 6) {
	    allSpots++;
	    spots[s] = i;
	    s++;
	}
    }

    char turn = parentState->getPlayerNum();

    for(;;) {
	//make move
	state[move][nextSpots[move]] = turn;
	nextSpots[move]++;

	//check win
	if(Play::checkWin(state, turn)) {
	    if(turn == playerNum) {
		return true;
	    } else {
		return false;
	    }
	}

	//check draw
	if(nextSpots[move] == 6) {
	    allSpots--;
	    if(!allSpots) {
		return false;
	    }

	    //patch?
	    for(int i = 0; i <= allSpots; i++) {
		if(spots[i] == move) {
		    spots[i] = spots[allSpots];
		    spots[allSpots] = -1;
		    break;
		}
	    }
	}

	// flip turn
	turn = Play::flipTurn(turn);

	//decide move
	move = spots[(rand() % allSpots)];
    }
}

//void printState(char** state) {
//    for(int i = NUM_ROWS - 1; i >= 0; i--) {
//        for(int j = 0; j < NUM_COLUMNS; j++) {
//            cerr << (int)state[j][i];
//        }
//        cerr << endl;
//    }
//}

