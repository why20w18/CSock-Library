#ifndef __CSOCK_MANUEL_HPP__
#define __CSOCK_MANUEL_HPP__

#include "csockDefines.hpp"
#include <unordered_map>
#include <iostream>

class csockManuel{
    /////////////////       /////   CSOCK MANUEL CROSS FUNCTION       /////   /////////////////

public:
    //internet to presentation => sayisal ip adresini stringe cevirir
    const char* csock_inetNtop(int ipv4v6,const void *connectedCfgAddr,char *buffer);
    
    //soket olusturup filedescriptor cevirir
    FILE_DESCRIPTOR csock_socket(CSOCK_INIT ipv4v6 , CSOCK_INIT tcp_udp);
    FILE_DESCRIPTOR csock_accept(int serverFD,struct sockaddr_in *connectedConfig,socklen_t *connectedConfigSize);
    
    //soketi kapatma
    void csock_close(int socketFD,bool cleanUp=false);
    void csock_closeAllClient(std::unordered_map<int,bool>& socketsMap);
    
    //bind zaten cross platformdur , parametreler duzenlendi
    bool csock_bind(int socketFD,struct sockaddr_in *socketConfig,unsigned int socketConfigSize);
    bool csock_listener();
    
    int csock_send(int socketFD,const char *data,unsigned int dataLength);
    int csock_recv(int socketFD,char *recvDataBuffer , unsigned int recvDataSize);

    void csock_sleep(unsigned int seconds);

    void csockMessage(const char *msg,CSOCK_INFO_LEVEL il=CSOCK_INFO,const char *currentFilename="MANUEL");

};






#endif //__CSOCK_MANUEL_HPP__