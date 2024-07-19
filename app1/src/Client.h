#pragma once
#include "Buffer.h"


class Client{
public:
    Client();
    void WriteThread();
    void ReadThread();

private:
    void SendDataToProgram2(int sum);
    bool InputIsDigit(const std::string& input);
    void CountingSort(std::string& input);

    Buffer buffer;
    std::mutex mtx;

};