#include "Client.h"
#include <thread>


int main(int argc, char *argv[])
{
    Client client;

    std::thread write_thread(&Client::WriteThread, &client);
    std::thread read_thread(&Client::ReadThread, &client);

    write_thread.join();
    read_thread.join();
    
}