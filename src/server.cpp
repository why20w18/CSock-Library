#include <iostream>
#include "../include/csock.hpp"

using namespace std;


int main(){

    //(1-2-3-4-5-6-7) 1 THREADDE CALISAN BLOCKING SERVER
    /*
    csock serverSocket(TCP,IPV4);
    serverSocket.setServer(CSOCK_DEFAULT_BACKLOG);
    sockaddr_in *serverConfig = serverSocket.setServerSocketConfig("127.0.0.1",CSOCK_DEFAULT_PORT);
    serverSocket.bindServerSock();

    //NFO
    bool serverIsRunning = serverSocket.serverResponser(true);
    serverSocket.socketInfo();
    */

    //(8) MULTITHREADING SERVER
    csock serverSocket(TCP,IPV4);
    serverSocket.setServer(CSOCK_DEFAULT_BACKLOG);
    sockaddr_in *serverConfig = serverSocket.setServerSocketConfig("127.0.0.1",CSOCK_DEFAULT_PORT);
    serverSocket.bindServerSock();
    serverSocket.serverResponserThread(true);
    

    return 0x0;
}   