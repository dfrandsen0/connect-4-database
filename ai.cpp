#include "ai.h"
#include "player.h"
#include "config.h"
#include "utility.h"
#include "state.h"
#include "play.h"

void AIBot::startGame() {
    this->internalState = Utility::makeEmptyState();
    this->internalState->setPlayerNum(this->playerNum_);
}

int AIBot::takeTurn() {
    Play::makeMove(this->internalState->getState(), 0, this->playerNum_);

    return 0;
}

void AIBot::informEnemyTurn(int move) {
    char enemyNum = 1;
    if(this->playerNum_ == 1) {
        enemyNum = 2;
    }
    Play::makeMove(this->internalState->getState(), move, enemyNum);
}

void AIBot::endGame() {

}
