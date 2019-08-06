#include <iostream>
#include <mutex>
#include <iostream>

// 이 코드는 데드락이 걸림
// 동일한 mutex를 여러 쓰레드에서 동시에 획득할 수 없음.

struct Math
{
    std::mutex mtx;
    int m_content;

    Math() :m_content(0){}


    void Multiplexer(int i)
    {
        std::lock_guard<std::mutex> lock(mtx);
        m_content *= i;
        std::cout<<"Multiplexer() is called. m_content = ";
        std::cout<<m_content<<std::endl;
    }

    void Divisor(int i)
    {
        std::lock_guard<std::mutex>lock(mtx);
        m_content /=i;
        std::cout<<"Divisor() is called. m_content = ";
        std::cout<<m_content<<std::endl;
    }

    void RunAll(int a)
    {
        std::lock_guard<std::mutex> lock(mtx);
        Multiplexer(a);
        Divisor(a);
    }

};


auto main() ->int
{
    Math math;
    math.RunAll(10);
    return 0;
}
