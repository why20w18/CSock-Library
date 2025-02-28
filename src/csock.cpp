#include "../include/csock.hpp"


std::unordered_map<int,bool> csock::socketsMap; //static define

//default olarak tcp/ipv4 olarak baslatir
CONFIG_INIT csock::csock(){
    this->optActive = 1;
    this->optDeactive = 0;

    this->initIP_V4_V6 = IPV4;
    this->initTCP_UDP = TCP;

    this->isServer = false;
    this->serverBacklog = 0;
    this->isSockConfigSet = false;
    this->clientConnectType = CSOCK_ONCE;


    this->socketFD = csockManuel::csock_socket(IPV4,TCP);
    
    t_clientConnected = sizeof(connectedClientConfig); 
    socketsMap[socketFD] = isServer;

}


//manuel constructor
CONFIG_INIT csock::csock(CSOCK_INIT tcp_udp, CSOCK_INIT ipv4_ipv6){
    this->optActive = 1;
    this->optDeactive = 0;

    this->initIP_V4_V6 = ipv4_ipv6;
    this->initTCP_UDP = tcp_udp;

    this->isServer = false;
    this->serverBacklog = 0;
    this->isSockConfigSet = false;
    this->clientConnectType = CSOCK_ONCE;


    this->socketFD = csockManuel::csock_socket(ipv4_ipv6,tcp_udp);
    
    t_clientConnected = sizeof(connectedClientConfig); 
    socketsMap[socketFD] = isServer;
}

//client icin yazilmis constructor otomatik baglanir 
//configurasyon gerektirmeyen constructor
DIRECT_INIT csock::csock(CSOCK_INIT tcp_udp , CSOCK_INIT ipv4_ipv6,const char *connectIP,unsigned int connectPortNo
    ,CSOCK_CONNECTION_OPTIONS once_stay){
    this->optActive = 1;
    this->optDeactive = 0;

    this->initIP_V4_V6 = ipv4_ipv6;
    this->initTCP_UDP = tcp_udp;

    this->isServer = false;
    this->serverBacklog = 0;

    this->socketFD = csockManuel::csock_socket(ipv4_ipv6,tcp_udp);
    t_clientConnected = sizeof(connectedClientConfig); 
    this->isSockConfigSet = false;
    this->clientConnectType = once_stay;

    
    socketsMap[socketFD] = isServer;
    setConnectedServerConfig(connectIP,connectPortNo);
    int connectStatus = connect(socketFD,(struct sockaddr*)&sockConnectConfig,sizeof(sockConnectConfig));
    if(connectStatus == -1){
        csockManuel::csockMessage("CONNECTION PROBLEM",CSOCK_ERROR,"BASE");
        std::cerr << errno << "\n";
    }
}


csock::~csock(){
    csock_close(socketFD,false);
}

int csock::sendData(const char *data){
    int sendedBytes = -1;
    if(isServer)
        sendedBytes = csock_send(clientFD,data,strlen(data));
    else 
        sendedBytes = csock_send(socketFD,data,strlen(data));

    return sendedBytes;
}

int csock::recvData(char *recvMessage,int recvMessageSize){
    memset(recvMessage,0,recvMessageSize);
    int receivedBytes = -1;
    
    if(isServer)
        receivedBytes = csock_recv(clientFD,recvMessage,recvMessageSize);
    else{
        receivedBytes = csock_recv(socketFD,recvMessage,recvMessageSize);        
    }
        
    return receivedBytes;
}


sockaddr_in* csock::setServerSocketConfig(const char *ipAddr,unsigned int portNo){
    if(this->isSockConfigSet){
        csockManuel::csockMessage("CONFIG ALREADY SETTED !",CSOCK_WARNING,"BASE");
        return nullptr;
    }
    this->sockServerConfig.sin_family = this->initIP_V4_V6;
    this->sockServerConfig.sin_port = htons(portNo);
    this->sockServerConfig.sin_addr.s_addr = inet_addr(ipAddr);
    memset(this->sockServerConfig.sin_zero,0,8);
    this->isSockConfigSet = true;
    return &sockServerConfig;
}

void csock::setServer(unsigned int serverBacklog){
    this->serverBacklog = serverBacklog;
    this->isServer = true;
    this->socketsMap[socketFD] = isServer;
}

sockaddr_in* csock::setConnectedServerConfig(const char *connectIpAddr, unsigned int portNo){
    if(this->isServer){
        csockManuel::csockMessage("SOCKET IS SERVER MODE !",CSOCK_ERROR,"BASE");
        return nullptr;
    }
    
    if(this->isSockConfigSet){
        csockManuel::csockMessage("CONFIG ALREADY SETTED !",CSOCK_WARNING,"BASE");
        return nullptr;
    }

    this->sockConnectConfig.sin_family = initIP_V4_V6;
    this->sockConnectConfig.sin_addr.s_addr = inet_addr(connectIpAddr);
    this->sockConnectConfig.sin_port = htons(portNo);
    memset(&this->sockConnectConfig.sin_zero,0,8);

    this->isSockConfigSet = true;

    return &sockConnectConfig;
}




bool csock::serverResponser(bool isInputed,const char *msgTitle,const char *loopMsg){
    if(isServer){
        int listenStaus = listen(this->socketFD,this->serverBacklog);
        if(listenStaus == -1){
            std::cerr << "SOCKET LISTEN PROBLEM" << std::endl;
            return false;
        }

        //server requester loop
        int sendedBytes = 0;
        std::cout << msgTitle << std::endl;
        std::string responseMessageFromServer;
        while(1){

            this->clientFD = csockManuel::csock_accept(socketFD,&connectedClientConfig,&t_clientConnected);
      
            std::cout << loopMsg << "\n";

            char buffer[1024];

            while(1){

                int reciviedBytes = recvData(buffer,sizeof(buffer));
                if(reciviedBytes <= 0){
                    csockManuel::csockMessage("CLIENT CONNECTION LOSTED",CSOCK_INFO,"BASE");
                    return false;
                }
                    
                std::cout << "ALINAN BYTE : " << reciviedBytes << "\n";
                if(!isInputed)
                    responseMessageFromServer = "SERVER OTOMATIK MESAJI KULLANICI GIRDISIZ";
                else{
                    std::cout << "\nSERVER INPUT : ";
                    
                    std::getline(std::cin,responseMessageFromServer);
                } 
                sendedBytes = sendData(responseMessageFromServer.c_str());

                std::cout << "GONDERILEN MESAJ : " << responseMessageFromServer << "\n";    
                std::cout << "GONDERILEN BYTE : " << send << "\n";
                std::cout << "GELEN MESAJ     : " << buffer << "\n";
                
                csockManuel::csock_inetNtop(initIP_V4_V6,&connectedClientConfig.sin_addr,buffer);
    
                DEBUG("FILE DESCRIPTOR : " << clientFD << " STR_IP : " << buffer);
            }
            
        }
        return true;
    }
    else
        csockManuel::csockMessage("SOCKET NOT SERVER MODE",CSOCK_ERROR,"BASE");
    return false;
}

void csock::clientRequester(bool isClientInputed){
    if(isServer){
        csockManuel::csockMessage("SOCKET IS SERVER MODE !",CSOCK_ERROR,"BASE");
        return;
    }

    char recvMessage[1024];
    short i = 0;
    
    if(this->clientConnectType == CSOCK_ONCE){
        if(!isClientInputed){
            memset(recvMessage,0,sizeof(recvMessage));

            sendData("REQUEST FROM CLIENT");
            recvData(recvMessage,sizeof(recvMessage));
            
            std::cout << "AUTO SENDED DATA : " << "REQUEST FROM CLIENT : CSOCK_DEFAULT_SLEEP UNTIL" << "\n";
            std::cout << "AUTO RECV   DATA : " << recvMessage << "\n";
        }
        else{
            memset(recvMessage,0,sizeof(recvMessage));
            std::string userInput;
            std::cout << "USER INPUT : ";
            std::getline(std::cin,userInput);
            sendData(userInput.c_str());
            recvData(recvMessage,sizeof(recvMessage));

            std::cout << "SENDED DATA : " << userInput << "\n";
            std::cout << "RECV   DATA : " << recvMessage << "\n";
        }

    }
    else if(this->clientConnectType == CSOCK_STAY){
        while(1){
            if(!isClientInputed){
                memset(recvMessage,0,sizeof(recvMessage));

                sendData("REQUEST FROM CLIENT : CSOCK_DEFAULT_SLEEP UNTIL");
                recvData(recvMessage,sizeof(recvMessage));
                
                std::cout << "AUTO SENDED DATA : " << "REQUEST FROM CLIENT : CSOCK_DEFAULT_SLEEP UNTIL" << "\n";
                std::cout << "AUTO RECV   DATA : " << recvMessage << "\n";
                i++;
                if(i == 5)
                    break;
                
                csock_sleep(1);
            }
            else{
                memset(recvMessage,0,sizeof(recvMessage));
                std::string userInput;
                std::cout << "USER INPUT : ";
                std::getline(std::cin,userInput);
                sendData(userInput.c_str());
                recvData(recvMessage,sizeof(recvMessage));

                std::cout << "SENDED DATA : " << userInput << "\n";
                std::cout << "RECV   DATA : " << recvMessage << "\n";

                if(userInput == "exit")
                    break;
            }
        }

    }

}


bool csock::connectServer(const char *connectIP,unsigned int connectPortNo){
    if(isServer){
        csockManuel::csockMessage("SOCKET IS SERVER MODE",CSOCK_ERROR,"BASE");
        return false;
    }
    if(isSockConfigSet){
        csockManuel::csockMessage("SOCKET CONFIG ALREADY SETTED !",CSOCK_ERROR,"BASE");
        return false;
    }
    
    setConnectedServerConfig(connectIP,connectPortNo);
    int connectStatus = connect(socketFD,(struct sockaddr*)&sockConnectConfig,sizeof(sockConnectConfig));
    if(connectStatus == -1){
        csockManuel::csockMessage("NOT CONNECTED",CSOCK_ERROR,"BASE");
        return false;
    }

    return true;
}

bool csock::connectServer(){
    if(isServer){
        csockManuel::csockMessage("SOCKET IS SERVER MODE",CSOCK_ERROR,"BASE");
        return false;
    }
    
    int connectStatus = connect(socketFD,(struct sockaddr*)&sockConnectConfig,sizeof(sockConnectConfig));
    if(connectStatus == -1){
        csockManuel::csockMessage("NOT CONNECTED",CSOCK_ERROR,"BASE");
        return false;
    }

    return true;
}

void csock::setClientConnection(CSOCK_CONNECTION_OPTIONS once_stay){
    if(!isServer)
    this->clientConnectType = once_stay;
    else 
    csockManuel::csockMessage("SOCKET IS SERVER MODE !",CSOCK_WARNING,"BASE");
}



//soketi yapilandirmaya baglama ama server
bool csock::bindServerSock(){
    return csockManuel::csock_bind(socketFD,&sockServerConfig,sizeof(sockServerConfig));
}

void csock::socketInfo(){
    std::cout << "\n[CSOCK-INFO] socketInfo()" << std::endl;
    std::cout << std::boolalpha << "IS SERVER SOCKET : " << this->isServer << std::endl;
    
    if(initTCP_UDP == 1)
        std::cout << "IPV4-IPV6 : " << "TCP - " << initTCP_UDP << std::endl;
    else if(initTCP_UDP == 2)
        std::cout << "IPV4-IPV6 : " << "UDP - " << initTCP_UDP << std::endl;
    
    if(initIP_V4_V6 == 2)
        std::cout << "TCP-UDP   : " << "IPV4 - " << initIP_V4_V6 << std::endl;
    else if(initIP_V4_V6 == 10)
        std::cout << "TCP-UDP   : " << "IPV6 - " << initIP_V4_V6 << std::endl;
    
}

void csock::allSockets(){
    for(auto &pair : socketsMap){
        std::cout << "FILE_DESCRIPTOR = " << pair.first << 
        std::boolalpha << " | IS_SERVER_SOCKET = " << pair.second << "\n";
    }
}





