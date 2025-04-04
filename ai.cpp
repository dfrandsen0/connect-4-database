#include <iostream>
#include <math.h>

#include "ai.h"
#include "player.h"
#include "config.h"
#include "utility.h"
#include "state.h"
#include "play.h"
#include "node.h"
#include "mcts.h"

using namespace std;

void AIBot::startGame() {
    State* rootState = Utility::makeEmptyState();
    this->root = new Node(rootState);
    this->currPosition = this->root;
}

int AIBot::takeTurn() {
    cout << "AI is thinking..." << endl;
    MCTS::startSimulation(this->currPosition, NUM_SIMS);

    int nextMove = findBestMove();

    makeMove(nextMove);

    return nextMove;
}

int AIBot::findBestMove() {
    bool* available = this->currPosition->getState()->getAvailable();
    Node** kids = this->currPosition->getChildren();

    int maxCount = 0;
    int maxIndex = -1;
    int defaultIndex = -1;

    for(int i = 0; i < NUM_CHILDREN; i++) {
	if(available[i]) {
	    cout << kids[i]->getFinished() << ": ";
	    double temp = Utility::calcUcb(kids[i], log(this->currPosition->getCount()));
	    cout << kids[i]->getCount() << ", " << kids[i]->getWins() << ": " << temp << endl;
	} else {
	    cout << "unavailable" << endl;
	}
    }

    for(int i = 0; i < NUM_CHILDREN; i++) {
	if(available[i]) {
	    if(kids[i]->getFinished() == NodeFinished::WIN) {
		return i;
	    } else if(kids[i]->getFinished() == NodeFinished::LOSE) {
		defaultIndex = i;
	    } else {
		if(kids[i]->getCount() > maxCount) {
		    maxCount = kids[i]->getCount();
		    maxIndex = i;
		}
	    }
	}
    }

    cout << "maxIndex: " << maxIndex << "; maxCount: " << maxCount << " default: " << defaultIndex << endl;

    if(maxIndex == -1) {
	return defaultIndex;
    } else {
	return maxIndex;
    }
}

void AIBot::makeMove(int move) {
    this->currPosition = this->currPosition->getChildren()[move];
}

void AIBot::informEnemyTurn(int move) {
    makeMove(move);
}

void AIBot::endGame() {

}

