#include "Client.h"
#include "iostream"


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
    int min = input[0], max = input[0];

    //решила полностью отказаться от импорта <algorithm>
    for (char ch : input)
    {
        if(min > ch ) min = ch;
        if(max < ch) max = ch;
    }
    int size_count_array = max - min + 1;
    int count_array[size_count_array, 0];

    for(char ch : input)
    {
        count_array[static_cast<int>(ch-min)]++;
    }

    input.clear();
    for (int i =size_count_array -1; i >= 0; --i)
    {
        input+=std::string(count_array[i], i+min +'0');
    }
}
//в конструкторе должна быть провекрка на кодировку консоли
void Client::WriteThread()
{
    while(true)
    {
        std::string input;
        std::cout << "Введите строку их цифр (длина строки должна быть < 65 символов)";
        std::getline(std::cin, input);
        //или можно было бы использовать std::all_of(input.begin(), input.end(), ::isdigit) из <algorithm>
        if (input.size() > 64 || !InputIsDigit(input)) 
        {
            std::cerr << "Некорректный ввод" <<std::endl;
            continue;
        }
        /* можно воспользоваться стандартным решением std::sort(input.rbegin(), input.rend());
        но оптимальнее будет использовать "Сортировку подсчетом", потому что
        ее временная сложность линейна, а сортировка стандартной библиотеки 
        имеет сложность O(n log(n)), а проблемная пространственная сложность 
        "Сортировки подсчетом" нивелируется за счет условий задачи (входной диапазон 0-9)
        и поэтому в худшем случае будет составлять O(n+10)*/
        CountingSort(input);
        for (auto iter = input.begin(); iter != input.end(); ++iter)
        {
            if (static_cast<int>(*iter) %2 ==0)
            {
                *iter = 'K';
                input.insert(iter,'B');
            } 
        }
        buffer.write(input);
    
    }
}