#ifndef __SOCKS_HPP__
#define __SOCKS_HPP__

#include "csockManuel.hpp"
#include <iostream>
#include <unordered_map> //tum soketleri static olarak listeleme

class csock : public csockManuel{
private:
    int socketFD;
    int clientFD;

    struct sockaddr_in sockServerConfig;     //server olacak soketin yapilandirmasi
    struct sockaddr_in connectedClientConfig;//serverin baglanan clientin verilerini tutacagi yapilandirma

    struct sockaddr_in sockConnectConfig;    //clientin baglanacagi serverin yapilandirmasi

    socklen_t t_clientConnected;

    static std::unordered_map<int,bool> socketsMap;                 //olusturulan soketlerin fd'lerini ve server olma durumunu tutar


    bool isServer;                                                  //server degilse listen edemesin
    unsigned int serverBacklog;

    int initTCP_UDP;
    int initIP_V4_V6;
    
    int optActive;
    int optDeactive;


public:
    csock(CSOCKS_INIT tcp_udp = TCP, CSOCKS_INIT ipv4_ipv6 = IPV4);               //soketi otomatik yapilandirma
    ~csock();                                                                     //destructor


    bool setSockOptions(int socketfd,CSOCKS_OPTIONS re_opt);         //socket set options re use port-ip
    void setServer(unsigned int serverBacklog);                      //soketi servera cevirme
  
    sockaddr_in* setServerSocketConfig(const char *ipAddr,unsigned int portNo,bool thisSocket);
    sockaddr_in* connectedServerConfig(const char *connectIpAddr, unsigned int portNo);

    bool bindServerSock();
    bool serverRequester(const char *msgTitle = "[CSOCK] SERVER LISTENING ...",const char *loopMsg = "1 ENDPOINT ACCEPTED");
    
    bool sendData(const char *data);                                //hem server hem client
    bool sendData(int data);                                        //hem server hem client
    bool recvData();                                                //hem server hem client

    int getSocketFD();                                              //soketi geri cevirir
    int* active();
    int* deactive();

    //NFO DECL
    void socketInfo();
    static void allSockets();

};


#endif 