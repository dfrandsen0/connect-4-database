#include <iostream>
#include <math.h>

#include "utility.h"
#include "state.h"
#include "node.h"
#include "mcts.h"
#include "play.h"
#include "human.h"
#include "ai.h"

//later passed by argv?
#define NUM_SIMS	1000000


using namespace std;

int main(int argc, char* argv[]) {

    AIBot* aiPlayer = new AIBot(1);
    Human* humanPlayer = new Human(2);

    aiPlayer->startGame();
    humanPlayer->startGame();

    //[choose who goes first here]

    Player* currPlayer = aiPlayer;
    Player* waitingPlayer = humanPlayer;
    Player* temp;

    State* baseState = Utility::makeEmptyState();

    int move;
    for(;;) {
	move = currPlayer->takeTurn();

	if(!Play::makeMove(baseState->getState(), move, baseState->getPlayerNum())) {
	    cout << "Failed to play " << move << endl;
	    return 1;
	}

	if(currPlayer->getPlayerType() == PlayerType::AI) {
	    cout << "The AI played in column " << move << "." << endl;
	}

	if(Play::checkWin(baseState->getState(), baseState->getPlayerNum())) {
	    if(currPlayer->getPlayerType() == PlayerType::AI) {
		cout << "The AI beat you!" << endl;
	    } else {
		cout << "You beat the AI!" << endl;
	    }
	    break;
	}

	if(Play::checkDraw(baseState->getState())) {
	    cout << "It's a draw!" << endl;
	    break;
	}

	waitingPlayer->informEnemyTurn(move);

	baseState->setPlayerNum(Play::flipTurn(baseState->getPlayerNum()));
	temp = currPlayer;
	currPlayer = waitingPlayer;
	waitingPlayer = temp;
    }

    return 0;
}

