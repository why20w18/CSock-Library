#include <iostream>
#include "../include/csock.hpp"

using namespace std;


int main(){

    csock serverSocket(TCP,IPV4);
    serverSocket.setServer(CSOCK_DEFAULT_BACKLOG);
    sockaddr_in *serverConfig = serverSocket.setServerSocketConfig("127.0.0.1",CSOCK_DEFAULT_PORT);
    serverSocket.bindServerSock();

    //NFO
    bool serverIsRunning = serverSocket.serverResponser(true);

    serverSocket.socketInfo();
    
    

    return 0x0;
}   