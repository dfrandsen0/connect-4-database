#ifndef SERVER_CONNECT_H_
#define SERVER_CONNECT_H_

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")

class ServerConnect {
private:
    SOCKET sock;
public:
    ServerConnect();
    ~ServerConnect();

    bool pullTree(Node* root);
    bool pushTree(Node* root);

};

#endif
