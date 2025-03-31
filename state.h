#ifndef STATE_H_
#define STATE_H_

class State {
private:
    char playerNum = 1;
    char** state = nullptr;
public:
    State();
    State(char playerNum);
    State(char playerNum, char** state);

    char getPlayerNum();
    void setPlayerNum(int playerNum);

    char** getState();
    void setState(char** state);

    char** copyState();
};

#endif

