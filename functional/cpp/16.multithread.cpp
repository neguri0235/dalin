#include <iostream>
#include <thread>

void threadProc()
{
    std::cout<<std::this_thread::get_id()<<std::endl;
}


auto main() ->int
{
    std::thread threads[5];

    for(int i = 0; i<5; i++)
    {
        //threads[i] = std::thread(threadProc);

        threads[i] = std::thread([]()
                                 {std::cout<<"Thread id ";
                                  std::cout<<std::this_thread::get_id()<<std::endl;});

    }

    for(auto& thread :threads)
    {
        thread.join();
    }

    return 0;
}
