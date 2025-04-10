#include <iostream>

#include "human.h"
#include "player.h"
#include "utility.h"
#include "state.h"
#include "play.h"

Human::~Human() {
    delete this->internalState;
}

void Human::startGame() {
    this->internalState = Utility::makeEmptyState();
    this->internalState->setPlayerNum(this->playerNum_);
}

int Human::takeTurn() {
    //interact with gui

    int yourMove;

    std::cerr << "Your turn!\n" << std::endl;
    printState();
    std::cerr << "Your move: ";
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
    Utility::printState(this->internalState->getState());
}
