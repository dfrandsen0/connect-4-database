#ifndef GUI_PLAYER_H
#define GUI_PLAYER_H

#include "player.h"
#include "state.h"

class GuiPlayer : public Player {
private:
    State* internalState;
public:
    GuiPlayer(char playerNum) : Player(PlayerType::GUI, playerNum) {}
    GuiPlayer(char playerNum, double cValue, int numSims) : Player(PlayerType::GUI, playerNum, cValue, numSims) {}

    ~GuiPlayer() override;

    void startGame() override;
    int takeTurn() override;
    void informEnemyTurn(int move) override;
    void endGame() override;
};

#endif
