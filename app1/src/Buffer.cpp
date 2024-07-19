#include "Buffer.h"
#include "thread"

void Buffer::write(const std::string& data)
{
    std::unique_lock<std::mutex> lock_buffer(mtx);
    cv.wait(lock_buffer, [this]{return !flag;}); //гарантия что поток 1 дождется потока 2
    buffer = data; 
    flag = true;
    cv.notify_one();
    //std::this_thread::sleep_for(std::chrono::microseconds(1000000));

}

std::string Buffer::read()
{
    std::unique_lock<std::mutex> lock_buffer(mtx);
    cv.wait(lock_buffer,[this]{return flag;});
    flag = false;
    return buffer;
}