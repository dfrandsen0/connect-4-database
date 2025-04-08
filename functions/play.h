#ifndef PLAY_H_
#define PLAY_H_

class Play {
public:
    static char flipTurn(char turn);
    static bool checkWin(char** state, char turn);

    // assumes a valid move given
    static bool makeMove(char** state, int move, char turn);
    static bool checkDraw(char** state);
};

#endif
