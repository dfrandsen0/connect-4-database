#ifndef STATE_H_
#define STATE_H_

class State {
private:
    char playerNum = 1;
    char** state = nullptr;
    bool* available = nullptr;
public:
    State();
    State(char playerNum);
    State(char playerNum, char** state);

    ~State();

    char getPlayerNum();
    void setPlayerNum(int playerNum);

    char** getState();
    void setState(char** state);

    char** copyState();

    bool* getAvailable();
    void setAvailable(bool* newAva);

};

#endif

