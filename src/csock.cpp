#include "../include/csock.hpp"


std::unordered_map<int,bool> csock::socketsMap; //static define

csock::csock(CSOCKS_INIT tcp_udp, CSOCKS_INIT ipv4_ipv6){
    this->optActive = 1;
    this->optDeactive = 0;

    this->initIP_V4_V6 = ipv4_ipv6;
    this->initTCP_UDP = tcp_udp;

    this->isServer = false;
    this->serverBacklog = 0;

    this->socketFD = csockManuel::csock_socket(ipv4_ipv6,tcp_udp);
    
    t_clientConnected = sizeof(connectedClientConfig); 
    socketsMap[socketFD] = isServer;
}

csock::~csock(){
    csock_close(socketFD,true);
}


sockaddr_in* csock::setServerSocketConfig(const char *ipAddr,unsigned int portNo,bool thisSocket){
    this->sockServerConfig.sin_family = this->initIP_V4_V6;
    this->sockServerConfig.sin_port = htons(portNo);
    this->sockServerConfig.sin_addr.s_addr = inet_addr(ipAddr);
    memset(this->sockServerConfig.sin_zero,0,8);

    return &sockServerConfig;
}

void csock::setServer(unsigned int serverBacklog){
    this->serverBacklog = serverBacklog;
    this->isServer = true;
    this->socketsMap[socketFD] = isServer;
}



bool csock::serverRequester(const char *msgTitle,const char *loopMsg){
    if(isServer){
        int listenStaus = listen(this->socketFD,this->serverBacklog);
        if(listenStaus == -1){
            std::cerr << "SOCKET LISTEN PROBLEM" << std::endl;
            return false;
        }

        //server requester loop
        std::cout << msgTitle << std::endl;
        while(1){

            this->clientFD = accept(socketFD,(sockaddr*)&connectedClientConfig,&t_clientConnected);
            std::cout << loopMsg << "\n";
            char buffer[1024];
            memset(buffer,0,1024);
            

            csockManuel::csock_inetNtop(initIP_V4_V6,&connectedClientConfig.sin_addr,buffer);

            DEBUG("FILE DESCRIPTOR : " << clientFD << " STR_IP : " << buffer);
        }


        return true;
    }
    else
        csockManuel::csockMessage("SOCKET NOT SERVER MODE",CSOCKS_ERROR);
    return false;
}


//soketi yapilandirmaya baglama ama server
bool csock::bindServerSock(){
    int bindStatus = bind(this->socketFD,(sockaddr*)&sockServerConfig,sizeof(sockServerConfig));
    if(bindStatus == -1){
        std::cerr << "SERVER BIND PROBLEM" << std::endl;
        return false;
    }

    return true;
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





