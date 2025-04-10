#include <iostream>
#include <math.h>
#include <unistd.h>
#include <fcntl.h>

#include "utility.h"
#include "state.h"
#include "config.h"
#include "node.h"

using namespace std;

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

double Utility::calcUcb(Node* node, double lnParentCount, double cValue) {
    return ((double)node->getWins() / (double)node->getCount()) + cValue * sqrt(lnParentCount / (double)node->getCount());
}

void Utility::printState(char** state) {
    for(int i = NUM_ROWS - 1; i >= 0; i--) {
        cerr << "|";
        for(int j = 0; j < NUM_COLUMNS; j++) {
            if(state[j][i] != 0) {
                cerr << (int)state[j][i];
            } else {
                cerr << " ";
            }
        }
        cerr << "|" << endl;
    }

    cerr << "---------" << endl;
}
