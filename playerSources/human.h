#ifndef HUMAN_H_
#define HUMAN_H_

#include "player.h"
#include "state.h"
#include "serverConnect.h"

class Human : public Player {
private:
    State* internalState;
public:
    Human(char playerNum) : Player(PlayerType::HUMAN, playerNum) {}
    Human(char playerNum, double cValue, int numSims) : Player(PlayerType::HUMAN, playerNum, cValue, numSims) {}
    Human(char playerNum, double cValue, int numSims, ServerConnect* sc) : Player(PlayerType::HUMAN, playerNum, cValue, numSims, sc) {}

    ~Human() override;

    void startGame() override;
    int takeTurn() override;
    void informEnemyTurn(int move) override;
    void endGame() override;

private:
    void printState();
};

#endif
