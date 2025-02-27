#ifndef __CSOCK_MANUEL_HPP__
#define __CSOCK_MANUEL_HPP__

#include "csockDefines.hpp"
#include <unordered_map>
#include <iostream>

class csockManuel{
    /////////////////       /////   CSOCK MANUEL CROSS FUNCTION       /////   /////////////////

public:
    //internet to presentation => sayisal ip adresini stringe cevirir
    const char* csock_inetNtop(int ipv4v6,const void *connectedCfgAddr,char *buffer , socklen_t bufferSize = INET_ADDRSTRLEN);
    
    //soket olusturup filedescriptor cevirir
    int csock_socket(CSOCKS_INIT ipv4v6 , CSOCKS_INIT tcp_udp);
    
    //soketi kapatma
    void csock_close(int socketFD,bool cleanUp=false);
    void csock_closeAllClient(std::unordered_map<int,bool>& socketsMap);
    
    //bind zaten cross platformdur
    
    
    void csockMessage(const char *msg,CSOCKS_INFO_LEVEL il=CSOCKS_INFO,const char *currentFilename="MANUEL");

};






#endif //__CSOCK_MANUEL_HPP__