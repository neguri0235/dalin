#include <iostream>
#include <mutex>
#include <thread>


using namespace std;


auto main() -> int
{

    std::mutex mtx;
    int counter = 0;

    std::thread threads[5];


    for(int i = 0; i<5; ++i)
    {

        threads[i] = std::thread([&counter, &mtx]()
                                 {
                                     for(int i=0; i<10000; ++i)
                                     {
                                         {
                                             std::lock_guard<mutex> guard(mtx);
                                             ++counter;
                                         }
                                     }

                                     std::cout<<std::this_thread::get_id();
                                     std::cout<<"\tCurrent counter = ";
                                     std::cout<<counter<<std::endl;
                                 });
    }


    for(auto& thread:threads)
    {
        thread.join();
    }

    std::cout<<counter<<std::endl;

    return 0;
}
