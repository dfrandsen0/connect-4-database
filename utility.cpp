
#include "utility.h"
#include "state.h"
#include "config.h"

State* Utility::makeEmptyState() {
    char** newState = new char*[NUM_COLUMNS];

    for(int i = 0; i < NUM_COLUMNS; i++) {
        newState[i] = new char[NUM_ROWS];
        for(int j = 0; j < NUM_ROWS; j++) {
            newState[i][j] = 0;
        }
    }

    State* result = new State(1, newState);
    return result;
}
