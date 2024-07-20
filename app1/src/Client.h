#pragma once
#include "Buffer.h"
#include <sys/socket.h>
#include <unistd.h>
#include <iostream>
#include <sys/un.h>


class Client{
public:
    Client();
    void WriteThread();
    void ReadThread();

private:
    void SendDataToProgram2(std::string sum);
    bool InputIsDigit(const std::string& input);
    void CountingSort(std::string& input);
    bool ConnectToServer();

    Buffer buffer;
    std::mutex mtx;

    int client_dsock; 
    struct sockaddr_un sock_addr;
    bool connected;





};