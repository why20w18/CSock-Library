#include "../include/csockManuel.hpp"

const char* csockManuel::csock_inetNtop(int ipv4v6,const void *connectedCfgAddr,char *buffer , socklen_t bufferSize){
    #ifdef CSOCK_PLATFORM_IS_WIN32
        return InetNtop(ipv4v6,connectedCfgAddr,buffer,bufferSize);
    #endif 

    #ifdef CSOCK_PLATFORM_IS_UNIX
        return inet_ntop(ipv4v6,connectedCfgAddr,buffer,bufferSize);
    #endif
}

int csockManuel::csock_socket(CSOCKS_INIT ipv4v6 , CSOCKS_INIT tcp_udp){
    int socketFD = -1;

    #ifdef CSOCK_PLATFORM_IS_WIN32
        WSADATA wsdata;
        WSAStartup(MAKEWORD(2,2),&wsdata);
        socketFD = socket(ipv4v6,tcp_udp,0);
        if(socketFD == -1){
            csockMessage("SOCKET NOT OPENED !",CSOCKS_ERROR);
            return -1;
        }
    #endif 

    #ifdef CSOCK_PLATFORM_IS_UNIX
        socketFD = socket(ipv4v6,tcp_udp,0);
        if(socketFD == -1){
            csockMessage("SOCKET NOT OPENED !",CSOCKS_ERROR);
            return -1;
        }

        return socketFD;
    #endif
}

//1 socket
void csockManuel::csock_close(int socketFD,bool cleanUp){
    #ifdef CSOCK_PLATFORM_IS_WIN32
        closesocket(socketFD);
        if(cleanUp)
            WSACleanup();  
    #endif 

    #ifdef CSOCK_PLATFORM_IS_UNIX
        close(socketFD);
    #endif
}

//serveri haric hepsini kapatma
void csockManuel::csock_closeAllClient(std::unordered_map<int,bool>& socketsMap){
    for(auto &pair : socketsMap){
        if(pair.second != true)
        csock_close(pair.first);
    }
    
    #ifdef CSOCK_PLATFORM_IS_WIN32
        WSACleanup();  
    #endif 
}


bool csockManuel::csock_bind(int socketFD,struct sockaddr_in *socketConfig,unsigned int socketConfigSize){
    int bindStatus = bind(socketFD,(sockaddr*)socketConfig,socketConfigSize);
    if(bindStatus == -1){
        csockMessage("SOCKET NOT BINDED",CSOCKS_ERROR);
        return false;
    }
    return true;
}


void csockManuel::csockMessage(const char *msg,CSOCKS_INFO_LEVEL il,const char *currentFilename){
    switch(il){
        case CSOCKS_INFO: std::cout << "[CSOCK-"<< currentFilename <<"-INFO] : " << msg << "\n";
        break;

        case CSOCKS_ERROR:
        std::cerr << "[CSOCK-"<< currentFilename <<"-ERROR] : " << msg << "\n";
        break;

        case CSOCKS_WARNING:
        std::cout << "[CSOCK-"<< currentFilename <<"-WARNING] : " << msg << "\n";
        break;
    };
}

