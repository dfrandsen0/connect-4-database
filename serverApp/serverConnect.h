#ifndef SERVER_CONNECT_H_
#define SERVER_CONNECT_H_

#include <winsock2.h>
#include <string>

#include "node.h"

using namespace std;

class ServerConnect {
public:
    ServerConnect();
    ~ServerConnect();
private:
    SOCKET openSocket();
    void sendPing(SOCKET sock);
public:
    bool pullTree(Node* root);
    bool pushTree(Node* root);
private:
    void pushTreeHelper(stringstream& ss, Node* node);
    void addNode(stringstream& ss, Node* node);
};

#endif
