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
    Node* pullTree();
    bool pushTree(Node* root);
private:
    void pushTreeHelper(stringstream& ss, Node* node);
    void addNode(stringstream& ss, Node* node);
    int bufferToNodes(char* stream, Node** nodes);
    void expandNode(Node* root, Node** nodeList, int nodeCount, char** reference);
    bool compareStates(char** state1, char** state2);
};

#endif
