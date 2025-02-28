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
    bool isSockConfigSet;
    unsigned int serverBacklog;

    //SOKETIN ORTAK OZELLIKLERI BIR NESNE YA SERVER YADA CLIENT OLABILIR
    int initTCP_UDP;
    int initIP_V4_V6;
    
    int optActive;
    int optDeactive;

    CSOCK_CONNECTION_OPTIONS clientConnectType;
    void serverNewConnectionProcessThread(bool isInputed,int newClientFD);


public:
    CONFIG_INIT csock();                                 //default olarak ipv4 ve tcp konfigurasyonu ile baslatma  ->server or client
    csock(CSOCK_INIT tcp_udp , CSOCK_INIT ipv4_ipv6);//soketi manuel olarak yapilandirma ->server or client
    csock(CSOCK_INIT tcp_udp , CSOCK_INIT ipv4_ipv6,const char *connectIP,unsigned int connectPortNo
    ,CSOCK_CONNECTION_OPTIONS clientConnectType=CSOCK_ONCE); //->client
    ~csock();                                                                     //destructor

    sockaddr_in* setServerSocketConfig(const char *ipAddr,unsigned int portNo);
    sockaddr_in* setConnectedServerConfig(const char *connectIpAddr, unsigned int portNo);


    bool setSockOptions(int socketfd,CSOCK_OPTIONS re_opt);         //socket set options re use port-ip
    void setServer(unsigned int serverBacklog);                      //soketi servera cevirme
  
   
    bool bindServerSock();
    bool serverResponser(bool isInputed = false,const char *msgTitle = "[CSOCK] SERVER LISTENING ...",const char *loopMsg = "1 ENDPOINT ACCEPTED");
    bool serverResponserThread(bool isInputed = false,const char *msgTitle = "[CSOCK] SERVER LISTENING ...",const char *loopMsg = "1 ENDPOINT ACCEPTED");
    

    CONFIG_INIT bool connectServer();   //konfigurasyondan sonra baslatma
    DIRECT_INIT bool connectServer(const char *connectIP,unsigned int connectPortNo); //konfigurasyonu icinde baslatir

    //CLASS ICINDEKI MEMBERLAR UZERINDEN CALISIR
    int sendData(const char *data);                                                       //hem server hem client
    int recvData(char *recvMessage,int recvMessageSize);                                   //hem server hem client

    //ISTENEN FILE DESCRIPTORA GORE CALISIR THREAD KISIM ICIN YAZILDI
    int sendData(int newClientFD,int newServerFD,const char *data);                             //hem server hem client
    int recvData(int newClientFD,int newServerFD,char *recvMessage,int recvMessageSize);        //hem server hem client
    

    
    //CLIENT BAGLANTISI NASIL KURULACAK//
    //default olarak baglanip yapacagi islemi yapip baglantiyi kapatir
    void setClientConnection(CSOCK_CONNECTION_OPTIONS once_stay);

    void clientRequester(bool isClientInputed = false);
    void clientRequesterThread(int newClientFD,bool isClientInputed = false);
    



    int getSocketFD();                                              //nesnenin kendisine atanmis soketi cevirir
    int* active();
    int* deactive();

    //NFO DECL
    void socketInfo();
    static void allSockets();

};


#endif 