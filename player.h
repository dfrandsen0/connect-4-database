#ifndef PLAYER_H_
#define PLAYER_H_

#include "config.h"

class Player {
protected:
    enum PlayerType playerType;// = PlayerT
    char playerNum_ = 1;
public:
    Player(enum PlayerType type, char playerNum) : playerType(type), playerNum_(playerNum) {}
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
