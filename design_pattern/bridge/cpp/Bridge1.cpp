
#include <iostream>

using namespace std;


struct IMP3 {
    virtual void Play()  = 0;
    virtual void Stop() = 0;
    virtual ~IMP3(){}
};

class IPod :public IMP3 {
public:
    void Play(){ cout<<"play ipod"<<endl;}
    void Stop(){ cout<<"stop ipod"<<endl;}
};

class People {
public:
    void UseMP3(IMP3* p) {
        p->Play();
        p->PlayOneMinute();  // PlayOneMinute() 를 추가하게 되면 모든 가상 함수를 사용하는 파생 클래스가 변경되어야 함.
    }
};

int main()
{


}
