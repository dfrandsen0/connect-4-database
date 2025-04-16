#include <winsock2.h>
#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
#include <cstring>
#include <cstdlib>

#include "serverConnect.h"
#include "node.h"
#include "config.h"
#include "coder.h"
#include "play.h"

using namespace std;

#define MAX_NODES   256

ServerConnect::ServerConnect() {
    WSADATA wsaData;
    int wsaResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (wsaResult != 0) {
        std::cerr << "WSAStartup failed: " << wsaResult << std::endl;
        return;
    }

    sendPing(openSocket());
}

ServerConnect::~ServerConnect() {
    WSACleanup();
}

SOCKET ServerConnect::openSocket() {
    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == INVALID_SOCKET) {
        std::cerr << "Socket creation failed" << std::endl;
        WSACleanup();
        return sock;
    }

    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8000);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (connect(sock, (sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        std::cerr << "Connection failed" << std::endl;
        closesocket(sock);
        WSACleanup();
        return sock;
    }

    return sock;
}

void ServerConnect::sendPing(SOCKET sock) {
    string httpRequest = "GET /ping HTTP/1.1\r\nHost: example.com\r\nContent-Type: application/json\r\n\r\n";

    send(sock, httpRequest.c_str(), httpRequest.length(), 0);

    // Receive and print the response
    char buffer[128];
    int bytesReceived;
    while ((bytesReceived = recv(sock, buffer, sizeof(buffer) - 1, 0)) > 0) {
        buffer[bytesReceived] = '\0';
        std::cerr << buffer;
    }
}

Node* ServerConnect::pullTree() {
    string httpRequest = "GET /getTree HTTP/1.1\r\nHost: example.com\r\nContent-Type: application/json\r\n\r\n";

    SOCKET sock = openSocket();

    send(sock, httpRequest.c_str(), httpRequest.length(), 0);
    
    char buffer[1048576];
    memset(buffer, 0, 1048576);
    int bytesReceived;
    int offset = 0;
    while ((bytesReceived = recv(sock, buffer + offset, sizeof(buffer) - 1, 0)) > 0) {
        offset += bytesReceived;
        std::cerr << buffer;
    }

    int contentLength = atoi(strstr(buffer, "Content-Length") + 16);
    if(contentLength < 4) {
        return nullptr;
    }

    char* body = strstr(buffer, "\r\n\r\n") + 4;

    Node* nodes[MAX_NODES];
    for(int i = 0; i < MAX_NODES; i++) {
        nodes[i] = nullptr;
    }

    int totalNodes = bufferToNodes(body, nodes);
    cerr << "parsed " << totalNodes << " nodes." << endl;

    char** referenceState = new char*[NUM_COLUMNS];
    for(int i = 0; i < NUM_COLUMNS; i++) {
        referenceState[i] = new char[NUM_ROWS];
        for(int j = 0; j < NUM_ROWS; j++) {
            referenceState[i][j] = 0;
        }
    }

    Node* root = nullptr;
    for(int i = 0; i < totalNodes; i++) {
        if(compareStates(referenceState, nodes[i]->getState()->getState())) {
            root = nodes[i];
            nodes[i] = nullptr;
        }
    }

    if(root == nullptr) {
        return nullptr;
    }

    root->getState()->setPlayerNum(1);

    expandNode(root, nodes, totalNodes, referenceState);

    for(int i = 0; i < NUM_COLUMNS; i++) {
        delete[] referenceState[i];
    }
    delete[] referenceState;

    return root;
}


bool ServerConnect::pushTree(Node* root) {
    stringstream ss;
    string headers = "POST /putTree HTTP/1.1\r\nHost: example.com\r\nContent-Type: application/json\r\nContent-Length: ";
    string endHeaders = "\r\n\r\n";

    ss << "[";

    pushTreeHelper(ss, root);

    string body = ss.str();
    //remove last comma
    body.pop_back();
    body += "]";

    SOCKET sock = openSocket();

    string httpRequest = headers + to_string(body.length());
    httpRequest += endHeaders;
    httpRequest += body;

    cerr << endl << httpRequest << endl << endl;

    send(sock, httpRequest.c_str(), httpRequest.length(), 0);

    char buffer[128];
    int bytesReceived;
    int offset = 0;
    while ((bytesReceived = recv(sock, buffer + offset, sizeof(buffer) - 1, 0)) > 0) {
        buffer[bytesReceived] = '\0';
        std::cerr << buffer;
    }
    
    return false;
}

void ServerConnect::pushTreeHelper(stringstream& ss, Node* node) {
    addNode(ss, node);

    // change to add more than one node?
    Node* bestNode = nullptr;
    int bestCount = 0;
    Node** children = node->getChildren();
    for(int i = 0; i < NUM_CHILDREN; i++) {
        if(children[i] != nullptr && children[i]->getCount() > bestCount) {
            bestCount = children[i]->getCount();
            bestNode = children[i];
        }
    }

    if(bestNode != nullptr) {
        pushTreeHelper(ss, bestNode);
    }
}

void ServerConnect::addNode(stringstream& ss, Node* node) {
    ss << "{\"_id\":\"";
    ss << Coder::base64_encode(Coder::encode(node->getState()->getState()));
    ss << "\",\"count\":" << node->getCount() << ",\"wins\":" << node->getWins();
    ss << "},";
}

int ServerConnect::bufferToNodes(char* stream, Node** nodes) {
    cerr << "Start parse" << endl;
    char* next = strstr(stream, "{");

    char* nextState;
    char* nextCountO;
    char* nextWinsO;

    int count;
    int wins;

    int index = 0;
    while(next != nullptr) {
        nextState = strstr(next, ":") + 2;
        string nextStateString(nextState, strstr(nextState, "\"") - nextState);
        // cerr << "nextState: " << nextStateString << "; ";

        char** state = new char*[NUM_COLUMNS];
        for(int i = 0; i < NUM_COLUMNS; i++) {
            state[i] = new char[NUM_ROWS];
            for(int j = 0; j < NUM_ROWS; j++) {
                state[i][j] = 0;
            }
        }

        Coder::decode(Coder::base64_decode(nextStateString), state);

        nextCountO = strstr(next, "count") + 7;
        string nextCountString(nextCountO, strstr(nextCountO, "\"") - nextCountO);
        count = stoi(nextCountString);

        nextWinsO = strstr(next, "wins") + 6;
        string nextWinsString(nextWinsO, strstr(nextWinsO, "}") - nextWinsO);
        wins = stoi(nextWinsString);

        // cerr << count << ", " << wins << endl;

        // for(int i = NUM_ROWS - 1; i >= 0; i--) {
        //     for(int j = 0; j < NUM_COLUMNS; j++) {
        //         cerr << (int)state[j][i];
        //     }
        //     cerr << endl;
        // }

        int count1 = 0;
        int count2 = 0;
        for(int i = 0; i < NUM_COLUMNS; i++) {
            for(int j = 0; j < NUM_ROWS; j++) {
                if(state[i][j] == 1) {
                    count1++;
                } else if(state[i][j] == 2) {
                    count2++;
                } else {
                    break;
                }
            }
        }

        State* newState = new State(1, state);

        Node* newNode = new Node(newState);
        nodes[index] = newNode;

        newNode->setCount(count);
        newNode->setWins(wins);

        if(count1 != count2) {
            newState->setPlayerNum(2);
            if(Play::checkWin(state, 1)) {
                newNode->setFinished(NodeFinished::WIN);
            } else if(Play::checkDraw(state)) {
                newNode->setFinished(NodeFinished::DRAW);
            }
        } else {
            if(Play::checkWin(state, 2)) {
                newNode->setFinished(NodeFinished::LOSE);
            } else if(Play::checkDraw(state)) {
                newNode->setFinished(NodeFinished::DRAW);
            }
        }

        index++;
        if(index == MAX_NODES) {
            return index;
        }

        next = strstr(next + 1, "{");
    }

    return index;
}

void ServerConnect::expandNode(Node* node, Node** nodeList, int nodeCount, char** reference) {
    bool* available = node->getState()->getAvailable();

    for(int i = 0; i < NUM_CHILDREN; i++) {
        if(available[i]) {
            Play::makeMove(reference, i, node->getState()->getPlayerNum());
            for(int j = 0; j < nodeCount; j++) {
                if(nodeList[j] == nullptr) {
                    continue;
                }

                if(compareStates(reference, nodeList[j]->getState()->getState())) {
                    node->setChild(nodeList[j], i);
                    nodeList[j] = nullptr;
                    expandNode(node->getChild(i), nodeList, nodeCount, reference);
                    break;
                }
            }

            Play::unMakeMove(reference, i);
        }
    }
}

bool ServerConnect::compareStates(char** state1, char** state2) {
    for(int i = 0; i < NUM_COLUMNS; i++) {
        for(int j = 0; j < NUM_ROWS; j++) {
            if(state1[i][j] != state2[i][j]) {
                return false;
            }
        }
    }

    return true;
}
