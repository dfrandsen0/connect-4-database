#include <iostream>

#include "config.h"
#include "coder.h"

int main(int argc, char* argv[]) {

    char** state = new char*[NUM_COLUMNS];
    for(int i = 0; i < NUM_COLUMNS; i++) {
        state[i] = new char[NUM_ROWS];
        for(int j = 0; j < NUM_ROWS; j++) {
            state[i][j] = 0;
        }
    }

    string example = "ABSA";

    Coder::decode(Coder::base64_decode(example), state);

    cout << "made it" << endl;
    return 0;
}


