#ifndef PLAY_H_
#define PLAY_H_

class Play {
public:
    static char flipTurn(char turn);
    static bool checkWin(char** state, char turn);
};

#endif
