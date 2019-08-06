#include <thread>
#include <iostream>

using std::cout;
using std::endl;

auto main() -> int
{
    int counter = 0;
    std::thread threads[5];

    for(int i=0; i<5; i++)
    {
        threads[i]= std::thread([&counter]()
                                {
                                    for(int i=0; i<10000; ++i)
                                    {
                                        ++counter;
                                        cout<<"Thread ID: ";
                                        cout<<std::this_thread::get_id();
                                        cout<<"\t Current Counter = ";
                                        cout<<counter<<endl;
                                    }
                                });
    }

    for(auto& thread : threads)
    {
        thread.join();
    }

    cout<<counter<<endl;

    return 0;
}
