#include <iostream>
#include <fstream>
#include <math.h>
#include <cstdlib>
#include <chrono>

#include "utility.h"
#include "state.h"
#include "node.h"
#include "mcts.h"
#include "play.h"
#include "human.h"
#include "ai.h"
#include "guiPlayer.h"

using namespace std;

int main(int argc, char* argv[]) {
    auto now = chrono::high_resolution_clock::now();
    auto seed = static_cast<unsigned int>(
        chrono::duration_cast<chrono::nanoseconds>(now.time_since_epoch()).count()
    );
    srand(seed);

    Player* firstPlayer;
    Player* secondPlayer;

    bool waitOnBots = false;
    if(argc > 1) {
		waitOnBots = atoi(argv[1]);
    }

    if(argc == 4) {
		firstPlayer = new AIBot(1, atol(argv[2]), atoi(argv[3]));
		secondPlayer = new GuiPlayer(2);
    } else if(argc == 6) {
		firstPlayer = new AIBot(1, atol(argv[2]), atoi(argv[3]));
		secondPlayer = new AIBot(2, atol(argv[4]), atoi(argv[5]));
    } else {
		waitOnBots = false;
		firstPlayer = new AIBot(1);
		secondPlayer = new Human(2);
    }

    firstPlayer->startGame();
    secondPlayer->startGame();

    //[choose who goes first here]

    Player* currPlayer = firstPlayer;
    Player* waitingPlayer = secondPlayer;
    Player* temp;

    State* baseState = Utility::makeEmptyState();

    int move;
    for(;;) {
		move = currPlayer->takeTurn();

		if(!Play::makeMove(baseState->getState(), move, baseState->getPlayerNum())) {
			cerr << "Failed to play " << move << endl;
			return 1;
		}

		//if(currPlayer->getPlayerType() == PlayerType::AI) {
			//cerr << "The AI played in column " << move << "." << endl;
		//}

		if(Play::checkWin(baseState->getState(), baseState->getPlayerNum())) {
			if(currPlayer->getPlayerType() == PlayerType::AI) {
				cerr << "The AI (" << (int)currPlayer->getPlayerNum() << ") beat you!" << endl;
			} else {
				cerr << "You beat the AI!" << endl;
			}

			ofstream res;
			res.open("tools/results.txt", ios::app);
			res << (int)currPlayer->getPlayerNum();
			res.close();

			break;
		}

		if(Play::checkDraw(baseState->getState())) {
			cerr << "It's a draw!" << endl;

			ofstream res;
			res.open("results.txt", ios::app);
			res << "0";
			res.close();

			break;
		}

		waitingPlayer->informEnemyTurn(move);

		baseState->setPlayerNum(Play::flipTurn(baseState->getPlayerNum()));
		temp = currPlayer;
		currPlayer = waitingPlayer;
		waitingPlayer = temp;

		if(waitOnBots) {
			Utility::printState(baseState->getState());
		}
    }

    //Utility::printState(baseState->getState());

    return 0;
}
