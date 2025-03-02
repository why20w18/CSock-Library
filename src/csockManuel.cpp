#include "../../include/csockManuel.hpp"

const char* csockManuel::csock_inetNtop(int ipv4v6,const void *connectedCfgAddr,char *buffer){
    #ifdef CSOCK_PLATFORM_IS_WIN32
        return InetNtop(ipv4v6,connectedCfgAddr,buffer,CSOCK_IP_STRLEN);
    #endif 

    #ifdef CSOCK_PLATFORM_IS_UNIX
        return inet_ntop(ipv4v6,connectedCfgAddr,buffer,CSOCK_IP_STRLEN);
    #endif
}

FILE_DESCRIPTOR csockManuel::csock_socket(CSOCK_INIT ipv4v6 , CSOCK_INIT tcp_udp){
    int socketFD = -1;

    #ifdef CSOCK_PLATFORM_IS_WIN32
        WSADATA wsdata;
        WSAStartup(MAKEWORD(2,2),&wsdata);
        socketFD = socket(ipv4v6,tcp_udp,0);
        if(socketFD == -1){
            csockMessage("SOCKET NOT OPENED !",CSOCK_ERROR);
            return -1;
        }
    #endif 

    #ifdef CSOCK_PLATFORM_IS_UNIX
        socketFD = socket(ipv4v6,tcp_udp,0);
        if(socketFD == -1){
            csockMessage("SOCKET NOT OPENED !",CSOCK_ERROR);
            return -1;
        }

    #endif

    return socketFD;
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
    int bindStatus = bind(socketFD,(struct sockaddr*)socketConfig,socketConfigSize);
    if(bindStatus == -1){
        csockMessage("SOCKET NOT BINDED",CSOCK_ERROR);
        return false;
    }
    return true;
}


bool csockManuel::csock_listener(){
    DEBUG("DEFINE EDILMEDI !");
}

int csockManuel::csock_send(int socketFD,const char *data,unsigned int dataLength){
    int sendedBytes = send(socketFD,data,dataLength,0);
    if(sendedBytes == -1){
        csockMessage("NOT SENDED DATA",CSOCK_ERROR);
        return -1;
    }

    return sendedBytes;
}

int csockManuel::csock_recv(int socketFD,char *recvDataBuffer , unsigned int recvDataSize){
    int receivedBytes = recv(socketFD,recvDataBuffer,recvDataSize,0); //server accept ile acilan soket uzerinden
                                                                     //client dogrudan kendi soketinden
    if(receivedBytes == -1){
        csockMessage("NOT RECEIVED DATA",CSOCK_ERROR);
        return -1;
    }
    return receivedBytes;
}


FILE_DESCRIPTOR csockManuel::csock_accept(int serverFD,struct sockaddr_in *connectedConfig,socklen_t *connectedConfigSize){
    int channelSocket = accept(serverFD,(struct sockaddr*)connectedConfig,connectedConfigSize);
    if(channelSocket == -1){
        csockMessage("NOT ACCEPTED CLIENT",CSOCK_ERROR);
        return -1;
    }

    return channelSocket;
}


void csockManuel::csock_sleep(unsigned int seconds){
    #ifdef CSOCK_PLATFORM_IS_WIN32
        Sleep(seconds);
    #endif 

    #ifdef CSOCK_PLATFORM_IS_UNIX
        sleep(seconds);
    #endif
}




void csockManuel::csockMessage(const char *msg,CSOCK_INFO_LEVEL il,const char *currentFilename){
    switch(il){
        case CSOCK_INFO: std::cout << "[CSOCK-"<< currentFilename <<"-INFO] : " << msg << "\n";
        break;

        case CSOCK_ERROR:
        std::cerr << "[CSOCK-"<< currentFilename <<"-ERROR] : " << msg << "\n";
        break;

        case CSOCK_WARNING:
        std::cout << "[CSOCK-"<< currentFilename <<"-WARNING] : " << msg << "\n";
        break;
    };
}

