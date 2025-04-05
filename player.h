#ifndef PLAYER_H_
#define PLAYER_H_

#include "config.h"

class Player {
protected:
    enum PlayerType playerType;// = PlayerT
    char playerNum_ = 1;
    double cValue = DEFAULT_C_VALUE;
    int numSims = DEFAULT_NUM_SIMS;
public:
    Player(enum PlayerType type, char playerNum) : playerType(type), playerNum_(playerNum) {}
    Player(enum PlayerType type, char playerNum, double cValue_, int numSims_) : playerType(type), playerNum_(playerNum), cValue(cValue_), numSims(numSims_) {}
    virtual ~Player();
    virtual void startGame() = 0;
    virtual int takeTurn() = 0;
    virtual void informEnemyTurn(int move) = 0;
    virtual void endGame() = 0;

    char getPlayerNum();
    void setPlayerNum(char playerNum);

    char getPlayerType();
    void setPlayerType(enum PlayerType playerType);


};

#endif
