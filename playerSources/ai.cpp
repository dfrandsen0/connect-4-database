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

AIBot::~AIBot() {
    delete this->root;
}

void AIBot::startGame() {
    State* rootState = Utility::makeEmptyState();
    this->root = new Node(rootState);
    this->currPosition = this->root;
}

int AIBot::takeTurn() {
//    cerr << "AI is thinking..." << endl;
    MCTS::startSimulation(this->currPosition, this->numSims, this->cValue);

    int nextMove = findBestMove();
	cout << nextMove;

    makeMove(nextMove);

    return nextMove;
}

int AIBot::findBestMove() {
    bool* available = this->currPosition->getState()->getAvailable();
    Node** kids = this->currPosition->getChildren();

    int maxCount = 0;
    int maxIndex = -1;
    int drawIndex = -1;
    int loseIndex = -1;
/*
    for(int i = 0; i < NUM_CHILDREN; i++) {
	if(available[i]) {
	    cerr << kids[i]->getFinished() << ": ";
	    double temp = Utility::calcUcb(kids[i], log(this->currPosition->getCount()), this->cValue);
	    cerr << kids[i]->getCount() << ", " << kids[i]->getWins() << ": " << temp << endl;
	} else {
	    cerr << "unavailable" << endl;
	}
    }
*/
    for(int i = 0; i < NUM_CHILDREN; i++) {
	if(available[i]) {
	    if(kids[i]->getFinished() == NodeFinished::WIN) {
		return i;
	    } else if(kids[i]->getFinished() == NodeFinished::DRAW) {
		drawIndex = i;
	    } else if(kids[i]->getFinished() == NodeFinished::LOSE) {
		loseIndex = i;
	    } else {
		if(kids[i]->getCount() > maxCount) {
		    maxCount = kids[i]->getCount();
		    maxIndex = i;
		}
	    }
	}
    }

//    cerr << "maxIndex: " << maxIndex << "; maxCount: " << maxCount << " lose: " << loseIndex << endl;//"; drawIndex: " << drawIndex << endl;

    if(maxIndex == -1) {
	if(drawIndex == -1) {
	    return loseIndex;
	} else {
	    return drawIndex;
	}
    } else {
	return maxIndex;
    }
}

void AIBot::makeMove(int move) {
    if(this->currPosition->getChildren()[move] == nullptr) {

	char nextPlayer = 1;
	if(this->currPosition->getState()->getPlayerNum() == 1) {
	    nextPlayer = 2;
	}

	char** newStateArray = this->currPosition->getState()->copyState();
	Play::makeMove(newStateArray, move, this->currPosition->getState()->getPlayerNum());

	State* newState = new State(nextPlayer, newStateArray);
	Node* newNode = new Node(newState);
	this->currPosition->setChild(newNode, move);
    }

    this->currPosition = this->currPosition->getChild(move);
}

void AIBot::informEnemyTurn(int move) {
    makeMove(move);
}

void AIBot::endGame() {

}

