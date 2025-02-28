//csockPlatform.hpp
#ifndef __CSOCK_PLATFORM_HPP__
#define __CSOCK_PLATFORM_HPP__

#ifdef _WIN32
    #include <winsock2.h>
    #include <ws2tcpip.h>
    #include <cstring>
    #include <windows.h>

    #pragma comment(lib, "ws2_32.lib")
    
    #define DEBUG(x) std::cout << "[DEBUG-MODE] : " << x << "\n"

    #define CSOCK_PLATFORM_IS_WIN32

#elif __linux__
    #include <sys/socket.h> //socket , bind , accept
    #include <arpa/inet.h>  //inet_addr
    #include <cstring>      //memset
    #include <unistd.h>     //close
    #include <netinet/in.h> //struct sockaddr_in
    

    #define DEBUG(x) std::cout << "[DEBUG-MODE] : " << x << "\n"
    #define CSOCK_PLATFORM_IS_UNIX 
#endif 


#endif //__CSOCK_PLATFORM_HPP__