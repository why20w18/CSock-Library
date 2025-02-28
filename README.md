# Cross Platform Socket Library 

## csock 2 parçadan oluşmaktadır:
```sh
	1-csockManuel dosyaları sayesinde cross platform soket işlemleri ve hata yakalama 
	  yapılır buradaki tüm metodlar csock_methodName şeklindedir , bind/accept gibi 
	  fonksiyonlar POSIX olduğundan ve WINSOCK API tarafından desteklendiğinden dolayı 
	  sadece hata yakalama düzenlenmiştir.
	2-csock dosyaları , csockManuel classından inherite edilerek hızlıca server ve client
	  kurulabilmesi için yazılmıştır , olabildiğince soyutlama ve özelleştirmeye izin
	  verecek şekilde yazılmaya çalışılmıştır.
```

### csock (base) 
 
 + csock nesnelerinin hepsi en başta default olarak client olarak başlar .setServer() metodu ile servera
   dönüştürülebilir böylece sockConnectConfig() gibi konfigürasyonlar otomatik engellenir aynı dosya
   içinde birden fazla soket oluşturulursa bunlar unordered_map içinde file descriptor ve server olma 
   durumuna göre tutulur , sockXxxx şeklindeki tüm configler mevcut soketin konfigürasyonu içindir
 
```sh
int socketFD;	//nesnenin soketi (client or server socket[.setServer(DEFAULT_BACKLOG)])
int clientFD;	//server durumunda accept ile açılan yeni soketi tutar (client socket)

struct sockaddr_in sockServerConfig; //server durumundaki soketin yapılandırması
struct sockaddr_in connectedClientConfig; //server durumundaki servera bağlanan client config

struct sockaddr_in sockConnectConfig;//client durumunda connect serverin configi

CONFIG_INIT csock() //default ipv4 ve tcp olarak baslatma server or client , config gereklidir
CONFIG_INIT csock(CSOCKS_INIT  tcp_udp , CSOCKS_INIT  ipv4_ipv6); //manuel baslatma server or client , konfigurasyon gerekir 
DIRECT_INIT csock(CSOCKS_INIT  tcp_udp , CSOCKS_INIT  ipv4_ipv6,const  char  *connectIP,
				  unsigned  int  connectPortNo); //sadece client config gerekmez direkt baglanir 


```





### csockManuel (manuel)
```sh
const char* csock_inetNtop()   -> unix - inet_ntop()/ winsock InetNtop()
FILE_DESCRIPTOR csock_socket() -> unix - socket()   / winsock WSADATA\WSAStartup\socket()
FILE_DESCRIPTOR csock_accept(struct sockaddr_in *) -> unix/winsock - accept(struct sockaddr *)

```



clientRequester --> soketin moduna gore otomatik send ve recv islemleri yapar uzun uzun yazmaktan kurtarir