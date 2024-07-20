#include "Server.h"

bool Server::Create()
{
    server_dsock = socket(AF_UNIX, SOCK_STREAM, 0);
    if(server_dsock == -1)
    {
        std::cerr <<"Не удалось создать сокет:\n";
        perror("socket");
        return false;
    }

    memset(&sock_addr, 0, sizeof(sockaddr_un));
 
    sock_addr.sun_family = AF_UNIX;

    //обрезает socket_name < 108 байт здесь возможно придеться преобразовать к строке.с_str()
    strncpy(sock_addr.sun_path, SOCKET_NAME, sizeof(sock_addr.sun_path) - 1);

    if (unlink(SOCKET_NAME) == -1 && errno != ENOENT) {
        std::cerr << "Не удалось удалить файл сокета: errno = " << errno << "\n";
        return false;
    }
    
    if(bind(server_dsock, (const struct sockaddr*)&sock_addr, sizeof(sockaddr_un)) == -1)
    {      
        std::cerr << "Ошибка связывания сокета со структурой: errno = " << errno << "\n"; 
        perror("bind");
        return false;
    }
    if(listen(server_dsock, 5) == -1)
    {
        perror("listen");
        return false;
    }
    std::cout<<"Сервер запущен и ожидает подключений..."<<std::endl;
    return true;
}

void Server::Process()
{
    //в случае пустой очереди поток заблокирется в ожидании соединений
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
        count_byte_get = recv(data_dsock, &buffer, SIZE_BUFFER, 0);
        if (count_byte_get < 1){
            if (count_byte_get == 0) {
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






