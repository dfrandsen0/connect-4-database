#ifndef HUMAN_H_
#define HUMAN_H_

#include "player.h"

class Human : public Player {
public:
    Human(char playerNum) : Player(PlayerType::HUMAN, playerNum) {}

    void startGame() override;
    int takeTurn() override;
    void informEnemyTurn(int move) override;
    void endGame() override;

private:
    void printState();
};

#endif
