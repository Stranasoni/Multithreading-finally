#include <sys/socket.h>
//#include <sys/types.h>
//#include <netinet/in.h>
#include <unistd.h>
#include <iostream>
//#include <cstring>
//#include <string>
#include <sys/un.h>

int main(int argc, char* argv[])
{
    int server_dsock = socket(AF_UNIX, SOCK_STREAM, 0);
    std::cout << server_dsock<<std::endl;
    int data_dsock;
    int count_byte_get;
    char buffer[3];//ограничение входной строки 64 максимальная сумма 9*64 = 576
    if(server_dsock == -1)
    {
        std::cerr <<"Не удалось создать сокет:\n";
        perror("socket");
        return 1;
    }

    struct sockaddr_un name;
    
    memset(&name, 0, sizeof(sockaddr_un));
 
    
    name.sun_family = AF_UNIX;
    std::string socket_name = "/tmp/server";
    //check socket_name <108 bait
    strncpy(name.sun_path, socket_name.c_str(), sizeof(name.sun_path)-1);
    
    if (unlink(socket_name.c_str()) == -1 && errno != ENOENT) {
        std::cerr << "Не удалось удалить файл сокета: errno = " << errno << "\n";
        return 1;
    }
    
    if(bind(server_dsock, (const struct sockaddr*)&name, sizeof(sockaddr_un)) == -1)
    {      
        std::cerr << "Ошибка связывания сокета со структурой: errno = " << errno << "\n"; 
        perror("bind");
        exit(1);
    }
    if(listen(server_dsock, 5) == -1)
    {
        std::cerr <<"Не удалось включить режим прослушивания соединений:" <<std::endl;
        perror("listen");
        return 1;
    }
    std::cout<<"Сервер запущен и ожидает подключений..."<<std::endl;

    //в случае пустой очереди поток заблокирется в ожидании соединений
    //data_dsock = accept(server_dsock, NULL, NULL);
    data_dsock = accept(server_dsock, NULL, NULL);
    while(true)
    {
        if(data_dsock == -1)
        {
            perror("accept");
            close(data_dsock);
            data_dsock = accept(server_dsock, NULL, NULL);
            continue;
        }
       //блокирует поток до нового send
        count_byte_get = recv(data_dsock, &buffer, 3, 0);//3 сделать надо?
        if (count_byte_get < 1){
            if (count_byte_get == 0) {
                // Соединение было закрыто на другом конце
                std::cerr << "Соединение закрыто на другом конце\n";
            } else 
                perror("recv");

            close(data_dsock);
            data_dsock = accept(server_dsock, NULL, NULL);
            continue;
        }
        
        if (count_byte_get > 2 && std::stoi(std::string(buffer))%32 == 0)
        {
            std::cout << "Получено " << count_byte_get << " байт данных: " << buffer << std::endl;
        }
        else 
             std::cout << "Ошибка: сумма меньше 2-ух символов или не кратна 32."<<std::endl;


    }
    close(data_dsock);
    close(server_dsock);
}
