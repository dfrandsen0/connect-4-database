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

double Utility::calcUcb(Node* node, double lnParentCount) {
    return ((double)node->getWins() / (double)node->getCount()) + C_VALUE * sqrt(lnParentCount / (double)node->getCount());
}

void Utility::waitForInput() {
    unsigned char temp;
    read(0, &temp, 1);

    fcntl(0, F_SETFL, fcntl(0, F_GETFL, 0) | O_NONBLOCK);

    while(read(0, &temp, 1) > 0) {}

    fcntl(0, F_SETFL, fcntl(0, F_GETFL, 0) & ~O_NONBLOCK);
}
