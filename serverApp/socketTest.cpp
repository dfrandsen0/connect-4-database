#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>
#include <iostream>
#include <algorithm>
#include <string>

#pragma comment(lib, "ws2_32.lib")  // Link with ws2_32.lib

using namespace std;

int main() {
    // Initialize Winsock
    WSADATA wsaData;
    int wsaResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (wsaResult != 0) {
        std::cerr << "WSAStartup failed: " << wsaResult << std::endl;
        return 1;
    }

    // Create a socket
    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == INVALID_SOCKET) {
        std::cerr << "Socket creation failed" << std::endl;
        WSACleanup();
        return 1;
    }

    // Set up the sockaddr_in structure
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8000);  // HTTP port
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Connect to localhost
    if (connect(sock, (sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        std::cerr << "Connection failed" << std::endl;
        closesocket(sock);
        WSACleanup();
        return 1;
    }

    // Send a simple HTTP GET request
    string headers = "POST / HTTP/1.1\r\nHost: example.com\r\nContent-Type: application/json\r\nContent-Length: ";

    string body = "[]";
    
    string contentLength = to_string(body.length());
    string endOfHeaders = "\r\n\r\n";
    string httpRequest = headers + contentLength + endOfHeaders + body;

    send(sock, httpRequest.c_str(), httpRequest.length(), 0);

    // Receive and print the response
    char buffer[4096];
    int bytesReceived;
    while ((bytesReceived = recv(sock, buffer, sizeof(buffer) - 1, 0)) > 0) {
        buffer[bytesReceived] = '\0';
        std::cout << buffer;
    }

    // Cleanup
    closesocket(sock);
    WSACleanup();

    return 0;
}
