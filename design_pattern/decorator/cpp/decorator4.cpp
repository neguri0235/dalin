#include <iostream>

using namespace std;

struct Compoment {
    virtual void Fire() = 0;
    virtual ~Compoment(){}
};

class SpaceCraft :public Compoment{
    int color;
    int speed;
public:
    void Fire() {
    cout<<"Space craft:-----"<<endl;
   }

};

class IDecorator : public Compoment {
    Compoment* craft = 0;
public:
    IDecorator(Compoment* p)  :craft(p){}
    void Fire() {
        craft->Fire();
    }
};


class LeftMissle  :public IDecorator{

public:
    LeftMissle(Compoment* sc) :IDecorator(sc) {

    }
    void Fire(){
        IDecorator::Fire();
        cout<<"Left missle:xxxxxx"<<endl;
    }
};


class RightMissle  :public IDecorator {
    Compoment* craft;
public:
    RightMissle(Compoment* sc) :IDecorator(sc){

    }
    void Fire(){
        IDecorator::Fire();
        cout<<"Right missle:>>>>>>"<<endl;
    }
};

int main()
{
    SpaceCraft sc;
    LeftMissle lm(&sc);

    RightMissle rm(&lm);
    rm.Fire();
    return 0;
}




