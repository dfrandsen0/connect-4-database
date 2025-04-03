#include <iostream>

#include "human.h"
#include "player.h"
#include "utility.h"
#include "state.h"
#include "play.h"

void Human::startGame() {
    this->internalState = Utility::makeEmptyState();
    this->internalState->setPlayerNum(this->playerNum_);
}

int Human::takeTurn() {
    //interact with gui

    int yourMove;

    std::cout << "Your turn!\n" << std::endl;
    printState();
    std::cout << "Your move: ";
    std::cin >> yourMove;

    //interact with gui

    Play::makeMove(this->internalState->getState(), yourMove, this->playerNum_);

    return yourMove;
}

void Human::informEnemyTurn(int move) {
    char enemyNum = 1;
    if(this->playerNum_ == 1) {
	enemyNum = 2;
    }
    Play::makeMove(this->internalState->getState(), move, enemyNum);
}

void Human::endGame() {
    //clean up
}

void Human::printState() {
    char** state = this->internalState->getState();
    for(int i = NUM_ROWS - 1; i >= 0; i--) {
	for(int j = 0; j < NUM_COLUMNS; j++) {
	    std::cout << (int)state[j][i];
	}
	std::cout << std::endl;
    }
}
