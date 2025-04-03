#ifndef PLAYER_H_
#define PLAYER_H_

class Player {
protected:
    char playerNum_ = 1;
public:
    Player(char playerNum) : playerNum_(playerNum) {}
    virtual ~Player();
    virtual void startGame(char yourPlayer) = 0;
    virtual int takeTurn() = 0;
    virtual void informEnemyTurn(int move) = 0;
    virtual void endGame() = 0;

    char getPlayerNum();
    void setPlayerNum(char playerNum);
};

#endif
