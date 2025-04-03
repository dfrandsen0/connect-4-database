#ifndef HUMAN_H_
#define HUMAN_H_

#include "player.h"


class Human : public Player {
public:
    Human(char playerNum) : Player(playerNum) {};

    void startGame(char yourPlayer) override;
    int takeTurn() override;
    void informEnemyTurn(int move) override;
    void endGame() override;
};

#endif
