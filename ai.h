#ifndef AI_H_
#define AI_H_

#include "player.h"
#include "node.h"
#include "config.h"

class AIBot : public Player {
private:
    Node* root;
    Node* currPosition;
public:
    AIBot(char playerNum) : Player(PlayerType::AI, playerNum) {}

    void startGame() override;
    int takeTurn() override;
private:
    int findBestMove();
    void makeMove(int move);
public:
    void informEnemyTurn(int move) override;
    void endGame() override;

};

#endif
