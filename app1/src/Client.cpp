#include "Client.h"
#include <thread>


Client::Client()
{
    ConnectToServer();
    std::cout << "Введите строку из цифр (максимум 64 символа):"<< std::endl;
}

bool Client::InputIsDigit(const std::string& input)
{
    for(char ch : input)
    {
        if (!(ch > 47 && ch < 58)) return false;
    }
    return true;
}

void Client::CountingSort(std::string& input)
{
    //алгоритм сортировки подсчетом
    int num = input[0] - '0';
    int min = num, max = num;
    
    //решила полностью отказаться от импорта <algorithm>
    for (int i =1; i < input.size(); ++i)
    {
        num = ((int)input[i] - '0');
        if(min > num) min = num;
        if(max < num ) max = num;
    }
    int size_count_array = max - min + 1;
    int count_array[size_count_array] {0};

    for(char ch : input)
    {
        num = ((int)ch - '0');
        count_array[num-min]++;
    }

    input.clear();
    for (int i =size_count_array -1; i >= 0; --i)
    {
        input+=std::string(count_array[i], i+min +'0');
    }
}

void Client::WriteThread()
{
    while(true)
    {
        std::string input;
        std::getline(std::cin, input);
        //или можно было бы использовать std::all_of(input.begin(), input.end(), ::isdigit) из <algorithm>
        if (input.size() > 64 || !InputIsDigit(input)) 
        {
            std::cerr << "Некорректный ввод" <<std::endl;
            continue;
        }
        /* можно воспользоваться стандартным решением std::sort(input.rbegin(), input.rend());
        но оптимальнее будет использовать "Сортировку подсчетом" */
        CountingSort(input);

        for (auto iter = input.begin(); iter != input.end(); ++iter)
        {
            int num = ((int)*iter - '0');
            if (num % 2 == 0)
            {
                *iter = 'B';
                input.insert(iter++,'K');
            } 
        }
        buffer.write(input);
    }
}

void Client::ReadThread()
{
    while(true)
    {
        std::string data = buffer.read();
        std::cout << "Полученные данные: " << data <<std::endl;

        int sum = 0;
        for (char ch :data)
        {
            if (ch !='K' && ch != 'B') sum+=(int)ch -'0';
        }
        SendDataToProgram2(std::to_string(sum));//нужно сделать оповещение отправлены ли данные программе 2
        std::cout << "Введите строку из цифр (максимум 64 символа):"<< std::endl;
    }
}

bool Client::ConnectToServer()
{
    client_dsock = socket(AF_UNIX, SOCK_STREAM, 0);
    if(client_dsock == -1){
        std::cout <<"Соединение с сервером не установлено:"<<std::endl;
        perror("socket");
        close(client_dsock);
        return false;
    }

    memset(&sock_addr, 0, sizeof(sock_addr));
    sock_addr.sun_family = AF_UNIX;
    strncpy(sock_addr.sun_path, SOCKET_NAME, sizeof(sock_addr.sun_path) -1);

    if(connect(client_dsock,(const sockaddr*)&sock_addr,sizeof(sock_addr)) == -1)
    {
        std::cout << "Не удалось подключиться к серверу. Возможно сервер не запущен.\n";
        perror("connect");
        close(client_dsock);
        return false;
    }
    connected = true;
    std::cout << "Подключение к серверу успешно.\n";
    return true;
}

void Client::SendDataToProgram2(std::string sum)
{
    if (!connected){
        if(!ConnectToServer()){
            std::cout << "Не удалось подключиться к серверу. Возможно сервер не запущен.\n";
            return;
        }
    }

    // MSG_NOSIGNAL вернет -1 если сервер не доступен  
    int count_byte_send = send(client_dsock, sum.c_str(), sum.size(), MSG_NOSIGNAL);
    if(count_byte_send == -1 && errno == EPIPE)
    {
        if (errno == EPIPE) std::cout << "Соединение закрылось на другом конце.\n";
        perror("send");
        close(client_dsock);
        connected = false;
        return;
    }
    
    std::cout <<"Данные отправлены\n";   

}

    
    






