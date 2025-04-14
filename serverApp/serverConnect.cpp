
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>
#include <iostream>
#include <algorithm>
#include <string>

#include "serverConnect.h"

#pragma comment(lib, "ws2_32.lib")

ServerConnect::ServerConnect() {
    WSADATA wsaData;
    int wsaResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (wsaResult != 0) {
        std::cerr << "WSAStartup failed: " << wsaResult << std::endl;
        return 1;
    }

    this->sock = socket(AF_INET, SOCK_STREAM, 0);
    if (this->sock == INVALID_SOCKET) {
        std::cerr << "Socket creation failed" << std::endl;
        WSACleanup();
        return 1;
    }

    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8000);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (connect(this->sock, (sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        std::cerr << "Connection failed" << std::endl;
        closesocket(this->sock);
        WSACleanup();
        return 1;
    }

    string httpRequest = "GET /ping HTTP/1.1\r\nHost: example.com\r\nContent-Type: application/json\r\n\r\n";
    send(sock, httpRequest.c_str(), httpRequest.length(), 0);

    char buffer[4096];
    int bytesReceived;
    while ((bytesReceived = recv(this->sock, buffer, sizeof(buffer) - 1, 0)) > 0) {
        buffer[bytesReceived] = '\0';
        std::cout << buffer;
    }

}

ServerConnect::~ServerConnect() {
    closesocket(this->sock);
    WSACleanup();
}

bool ServerConnect::pullTree(Node* root) {

}

bool ServerConnect::pushTree(Node* root) {

}
