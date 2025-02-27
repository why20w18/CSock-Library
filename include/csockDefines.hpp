//csockDefines.hpp
#ifndef __CSOCK_DEFINES_HPP__
#define __CSOCK_DEFINES_HPP__

#include "csockPlatform.hpp"

enum CSOCKS_INIT{
    IPV4 = AF_INET,
    IPV6 = AF_INET6,
    TCP = SOCK_STREAM,
    UDP = SOCK_DGRAM
};

enum CSOCKS_OPTIONS{
    RE_ALL = SO_REUSEADDR,
    DEFAULT_BACKLOG = 5,
};

enum CSOCKS_INFO_LEVEL{
    CSOCKS_WARNING,
    CSOCKS_ERROR,
    CSOCKS_INFO
};




#endif //__CSOCK_DEFINES_HPP__