
#include "config.h"
#include "state.h"

State::State() {}

State::State(char playerNum = 1) {
    this->playerNum = playerNum;
}

State::State(char playerNum = 1, char** state = nullptr) {
    this->playerNum = playerNum;
    this->state = nullptr;
}

char State::getPlayerNum() {
    return this->playerNum;
}

void State::setPlayerNum(int playerNum) {
    this->playerNum = playerNum;
}

char** State::getState() {
    return this->state;
}

void State::setState(char** state) {
    this->state = state;
}

char** State::copyState() {
    char** newState = new char*[NUM_COLUMNS];

    for(int i = 0; i < NUM_COLUMNS; i++) {
	newState[i] = new char[NUM_ROWS];
	for(int j = 0; j < NUM_ROWS; j++) {
	    newState[i][j] = this->state[i][j];
	}
    }

    return newState;

}
