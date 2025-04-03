
#include "player.h"

Player::~Player() {}

char Player::getPlayerNum() {
    return this->playerNum_;
}

void Player::setPlayerNum(char playerNum) {
    this->playerNum_ = playerNum;
}


