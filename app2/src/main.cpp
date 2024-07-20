#include "Server.h"

int main(int argc, char* argv[])
{
    Server divine_server;
    if(divine_server.Create())
    {
        divine_server.Process();
    }
      
}
