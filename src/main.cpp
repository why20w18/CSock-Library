#include <iostream>
#include "../include/csockPlatform.hpp"
#include "../include/csock.hpp"

using namespace std;


int main(){

    csock serverSocket(TCP,IPV4);
    serverSocket.setServer(10);
    sockaddr_in *serverConfig = serverSocket.setServerSocketConfig("127.0.0.1",8085,true);
    serverSocket.bindServerSock();

    //NFO
    csock clientSocket(UDP,IPV6);
    csock::allSockets();

    bool serverIsRunning = serverSocket.serverRequester();


    serverSocket.socketInfo();
    
    

    return 0x0;
}   