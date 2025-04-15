#include <winsock2.h>
#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>

#include "serverConnect.h"
#include "node.h"
#include "config.h"
#include "coder.h"

using namespace std;

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
    char buffer[4096];
    int bytesReceived;
    while ((bytesReceived = recv(sock, buffer, sizeof(buffer) - 1, 0)) > 0) {
        buffer[bytesReceived] = '\0';
        std::cout << buffer;
    }
}

bool ServerConnect::pullTree(Node* root) {
    return false;
}

bool ServerConnect::pushTree(Node* root) {
    stringstream ss;
    string headers = "POST /putTree HTTP/1.1\r\nHost: example.com\r\nContent-Type: application/json\r\nContent-Length: ";
    string endHeaders = "\r\n\r\n";

    ss << "[";

    pushTreeHelper(ss, root);

    // ss << ",";

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
    // string httpRequest = "GET /ping HTTP/1.1\r\nHost: example.com\r\nConnection: keep-alive\r\nContent-Type: application/json\r\n\r\n";
    // int result = send(sock, httpRequest.c_str(), httpRequest.length(), 0);
    // if (result == SOCKET_ERROR) {
    //     cerr << "send failed: " << WSAGetLastError() << endl;
    //     return false;
    // }

    char buffer[4096];
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
    ss << "{\"state\":\"";
    ss << Coder::base64_encode(Coder::encode(node->getState()->getState()));
    ss << "\",\"count\":" << node->getCount() << ",\"wins\":" << node->getWins();
    ss << "},";

    //{"state":"string",
}