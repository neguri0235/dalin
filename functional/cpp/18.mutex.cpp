#include <thread>
#include <mutex>
#include <iostream>

auto main() -> int
{
    std::mutex mtx;
    int counter = 0;

    std::thread threads[5];

    for(int i = 0; i<5; ++i)
    {
        threads[i] = std::thread(
                [&counter,&mtx](){
                    for(int i = 0; i<10000; ++i)
                    {
                        mtx.lock();
                        ++counter;
                        mtx.unlock();
                        std::cout<<"Thread ID: ";
                        std::cout<<std::this_thread::get_id();
                        std::cout<<"\tCurrent Counter = ";
                        std::cout<<counter<<std::endl;
                    }
        }
     );
    }

    for(auto& thd :threads){
        thd.join();
    }

    std::cout<<counter<<std::endl;
    return 0;
}
