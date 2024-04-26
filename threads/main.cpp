#include <iostream>
#include <thread>
#include <mutex>

int g_value;
std::mutex g_incrementMtx;

void print() 
{
    std::cout << g_value << std::endl;
}

void increment()
{
    while(true)
    {
        std::unique_lock<std::mutex> lock(g_incrementMtx);
        g_value++;
        lock.unlock();
    }
}

void read()
{
    while(true)
    {
        std::unique_lock<std::mutex> lock(g_incrementMtx);
        print();
        lock.unlock();
    }
}

int main() {
    std::thread th1(increment);
    std::thread th2(read);

    th1.join();
    th2.join();

    return 0;
}