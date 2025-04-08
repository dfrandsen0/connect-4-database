#include "player.h"
#include "config.h"

Player::~Player() {}

char Player::getPlayerNum() {
    return this->playerNum_;
}

void Player::setPlayerNum(char playerNum) {
    this->playerNum_ = playerNum;
}

char Player::getPlayerType() {
    return this->playerType;
}

void Player::setPlayerType(enum PlayerType playerType) {
    this->playerType = playerType;
}


