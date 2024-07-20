#include <sys/socket.h>
#include <unistd.h>
#include <iostream>
#include <sys/un.h>

#define SIZE_BUFFER 3 //ограничение входной строки 64 максимальная сумма 9*64 = 576
#define SOCKET_NAME "/tmp/my_divine_server"


class Server 
{
public:
    void Process();
    bool Create();

private:
    int server_dsock, data_dsock;
    int count_byte_get;
    char buffer[SIZE_BUFFER]; 
    struct sockaddr_un sock_addr;
};
