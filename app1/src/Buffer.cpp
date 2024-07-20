#include "Buffer.h"
#include "thread"

void Buffer::write(const std::string& data)
{
    std::unique_lock<std::mutex> lock_buffer(mtx);
    cv.wait(lock_buffer, [this]{return !flag;}); //гарантия что поток 1 дождется потока 2
    buffer = data; 
    flag = true;
    cv.notify_one();
    

}

std::string Buffer::read()
{
    std::unique_lock<std::mutex> lock_buffer(mtx);
    cv.wait(lock_buffer,[this]{return flag;});
    flag = false;
    return buffer;
}