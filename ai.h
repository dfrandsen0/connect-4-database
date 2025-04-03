#ifndef AI_H_
#define AI_H_

#include "player.h"


class AIBot : public Player {
public:
    AIBot(char playerNum) : Player(PlayerType::AI, playerNum) {}

    void startGame() override;
    int takeTurn() override;
    void informEnemyTurn(int move) override;
    void endGame() override;
};

#endif
