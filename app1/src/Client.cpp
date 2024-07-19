#include "Client.h"
#include "iostream"
#include <thread>

Client::Client()
{}

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
        std::cout << "Введите строку из цифр (максимум 64 символа):"<< std::endl;
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
        //для последовательного вывода в консоль
        std::this_thread::sleep_for(std::chrono::microseconds(1));
    
    }
}

void Client::ReadThread()
{
    while(true)
    {
        std::string data = buffer.read();
        std::cout << "Полученные данные: " << data <<std::endl;

        int sum;
        for (char ch :data)
        {
            if (ch !='K' && ch != 'B') sum+=(int)ch -'0';
        }
        SendDataToProgram2(sum);//нужно сделать оповещение отправлены ли данные программе 2
    }
}

void Client::SendDataToProgram2(int sum)
{

}




