#include "Buffer.h"

void Buffer::write(const std::string& data)
{
    std::unique_lock<std::mutex> lock_buffer(mtx);
    buffer = data; //общий буфер затирается, где гарантия того что поток 2 успеет прочитать

}

std::string Buffer::read()
{
    std::unique_lock<std::mutex> lock_buffer(mtx);
    return buffer;
}