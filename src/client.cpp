#include <iostream>
#include "../include/csock.hpp"

using namespace std;


int main(){
    //(1) OTOMATIK BASLATMA
    /* 
    csock clientSocket(TCP,IPV4,"127.0.0.1",8085);
    char buffer[1024];
    clientSocket.sendData("Merhaba Server");
    clientSocket.recvData(buffer,sizeof(buffer));
    std::cout << "SERVERIN GONDERDIGI MESAJ : " << buffer << "\n";
    clientSocket.socketInfo();
    */
    



    //(2) MANUEL BASLATMA - SOCKET CONFIG ALREADY SETTED ERR (DEGISTIRILDI SADECE INFO VERIYOR)
    /*
    csock clientSocket; //tcp ipv4 olarak basladi
    clientSocket.setConnectedServerConfig("127.0.0.1",8085);
    clientSocket.connectServer("127.0.0.1",8085);
    */





    //(3) MANUEL BASLATMA - 1
    /*
    csock clientSocket; //tcp ipv4 olarak basladi
    clientSocket.setConnectedServerConfig("127.0.0.1",8085);
    clientSocket.connectServer();
    */





    //(4) MANUEL BASLATMA - 2
    /*
    csock clientSocket; //tcp ipv4 olarak basladi
    clientSocket.connectServer("127.0.0.1",8085);
    */






    //(5) STAY MOD MANUEL MESAJ GONDERME ALMA 
    /*
    csock clientSocket(TCP,IPV4,"127.0.0.1",8085,CSOCK_STAY);
    char buffer[1024];
    clientSocket.sendData("Merhaba Server");
    clientSocket.recvData(buffer,sizeof(buffer));
    std::cout << "SERVERIN GONDERDIGI MESAJ : " << buffer << "\n";
    clientSocket.socketInfo();
    */






    //(6) STAY MODDA OTOMATIK MESAJ GONDERME
    /*
    csock clientSocket; //otomatik tcp ipv4 basladi
    clientSocket.setConnectedServerConfig("127.0.0.1",8085);
    clientSocket.setClientConnection(CSOCK_STAY);   //stay moda aldik
    clientSocket.connectServer();
    clientSocket.clientRequester(false); //otomatik mesaj gonderecek
    clientSocket.socketInfo();
    */





    //(7) STAY MODDA CLIENT MESAJ GONDERSIN
    /*
    csock clientSocket; //otomatik tcp ipv4 basladi
    sockaddr_in *clientConnectedServerCFG = clientSocket.setConnectedServerConfig("127.0.0.1",8085);
    clientSocket.setClientConnection(CSOCK_STAY);   //stay moda aldik
    clientSocket.connectServer();
    clientSocket.clientRequester(true); //otomatik mesaj gondermeyecek client girdi girmeli
    clientSocket.socketInfo();
    */
    
    //(8) STAY MODDA MULTITHREAD SERVERA BIRDEN FAZLA MESAJ YOLLAMA
    csock clientSocket(TCP,IPV4,"127.0.0.1",CSOCK_DEFAULT_PORT,CSOCK_STAY);
    clientSocket.clientRequester(true);
    




    return 0x0;
}   