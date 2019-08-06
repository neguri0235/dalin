#include <iostream>
#include <thread>
#include <chrono>

void threadProc()
{
    std::cout<<"Thread ID: "<<std::this_thread::get_id()<<std::endl;

    for(int i = 0; i<5; i++)
    {
        std::cout<<"thread: "<<i<<std::endl;
    }
}

auto main() -> int
{
    std::thread thread1(threadProc);

    for(int i = 0; i<5; i++)
    {
        std::cout<<"main thread:"<<i<<std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(2));
    }

    thread1.join();
    return 0;
}
