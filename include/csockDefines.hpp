//csockDefines.hpp
#ifndef __CSOCK_DEFINES_HPP__
#define __CSOCK_DEFINES_HPP__

#include "csockPlatform.hpp"

typedef int FILE_DESCRIPTOR;
typedef unsigned int uint;
#define CSOCK_DIRECT_INIT
#define CSOCK_CONFIG_INIT
#define CSOCK_IP_STRLEN 16  //'255.255.255.255' + '\0' 
                            // 3+1+3+1+3+1+3+1  +  1 => 16byte MAX

enum CSOCK_INIT{
    IPV4 = AF_INET,
    IPV6 = AF_INET6,
    TCP = SOCK_STREAM,
    UDP = SOCK_DGRAM
};

enum CSOCK_OPTIONS{
    CSOCK_RE_ALL = SO_REUSEADDR,
};

enum CSOCK_DEFAULT_PARAMS{
    CSOCK_DEFAULT_BACKLOG = 5,
    CSOCK_DEFAULT_SLEEP = 5,
    CSOCK_DEFAULT_PORT = 8085,
    CSOCK_DEFAULT_IFADDRS_COUNT = 3 
};

enum CSOCK_INFO_LEVEL{
    CSOCK_WARNING,
    CSOCK_ERROR,
    CSOCK_INFO
};

enum CSOCK_CONNECTION_OPTIONS{
    CSOCK_ONCE,  //bir defa baglan ve kop 
    CSOCK_STAY   //bagli kal
};



#endif //__CSOCK_DEFINES_HPP__