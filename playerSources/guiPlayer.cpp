#include <iostream>

#include "guiPlayer.h"
#include "player.h"
#include "utility.h"
#include "state.h"
#include "play.h"

void GuiPlayer::startGame() {
    this->internalState = Utility::makeEmptyState();
    this->internalState->setPlayerNum(this->playerNum_);
}

int GuiPlayer::takeTurn() {
    //interact with gui

    int yourMove;
    std::cin >> yourMove;
    Play::makeMove(this->internalState->getState(), yourMove, this->playerNum_);

    return yourMove;
}

void GuiPlayer::informEnemyTurn(int move) {
    char enemyNum = 1;
    if(this->playerNum_ == 1) {
	    enemyNum = 2;
    }

    Play::makeMove(this->internalState->getState(), move, enemyNum);
}

void GuiPlayer::endGame() {
    //clean up
}