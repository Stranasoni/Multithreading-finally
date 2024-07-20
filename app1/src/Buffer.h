#pragma once
#include <mutex>
#include <string>
#include <condition_variable>

//Полагаю что в буфере храниться только одна строка. Это правильно, потому что результат становиться ожидаемым.
class Buffer{
public:
    void write(const std::string& data);
    std::string read();
    
private:
    std::string buffer;
    std::mutex mtx;
    std::condition_variable cv;
    bool flag = false;
};