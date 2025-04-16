#include "play.h"
#include "config.h"


char Play::flipTurn(char turn) {
    if(turn == 1) {
	return 2;
    } else {
	return 1;
    }
}

bool Play::checkWin(char** state, char player) {
    int count;

    // vertical checks
    for(int i = 0; i < NUM_COLUMNS; i++) {
        count = 0;
        if(state[i][MIDDLE_ROW] != player) { continue; }

        for(int j = 0; j < NUM_ROWS; j++) {
            if(state[i][j] == player) {
                count++;
                if(count >= WIN_LENGTH) {
                    return true;
                }
            } else {
                count = 0;
            }
        }
    }

    // horizontal checks
    for(int i = 0; i < NUM_ROWS; i++) {
        count = 0;
        if(state[MIDDLE_COLUMN][i] != player) { continue; }

        for(int j = 0; j < NUM_COLUMNS; j++) {
            if(state[j][i] == player) {
                count++;
                if(count >= WIN_LENGTH) {
                    return true;
                }
            } else {
                count = 0;
            }
        }
    }

    // diagonal \ checks
    for(int i = WIN_LENGTH - 1; i < NUM_ROWS; i++) {
        for(int j = 0; j <= NUM_COLUMNS - WIN_LENGTH; j++) {
            count = 0;
            for(int k = 0; k < WIN_LENGTH; k++) {
                if(state[j + k][i - k] != player) {
                    break;
                }
                count++;
            }

            if(count == WIN_LENGTH) {
                return true;
            }
        }
    }

    // diagonal / checks
    for(int i = 0; i <= NUM_COLUMNS - WIN_LENGTH; i++) {
        for(int j = 0; j <= NUM_ROWS - WIN_LENGTH; j++) {
            count = 0;
            for(int k = 0; k < WIN_LENGTH; k++) {
                if(state[i + k][j + k] != player) {
                    break;
                }
                count++;
            }

            if(count == WIN_LENGTH) {
                return true;
            }
        }
    }

    return false;
}

bool Play::makeMove(char** state, int move, char turn) {
    for(int i = 0; i < NUM_ROWS; i++) {
	if(state[move][i] == 0) {
	    state[move][i] = turn;
	    return true;
	}
    }
    return false;
}

bool Play::unMakeMove(char** state, int move) {
    if(state[move][0] == 0) {
        return false;
    }

    for(int i = 1; i < NUM_ROWS; i++) {
        if(state[move][i] == 0) {
            state[move][i - 1] = 0;
            break;
        }
    }

    state[move][NUM_ROWS - 1] = 0;
    return true;
}

bool Play::checkDraw(char** state) {
    for(int i = 0; i < NUM_COLUMNS; i++) {
	if(state[i][NUM_ROWS - 1] == 0) {
	    return false;
	}
    }

    return true;
}
