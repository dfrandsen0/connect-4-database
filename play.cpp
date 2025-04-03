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
