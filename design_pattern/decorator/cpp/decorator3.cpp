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
    Compoment* craft ;
public:

    IDecorator(Compoment* p)  :craft(p){}



};


class LeftMissle  :public Compoment{
    Compoment* craft;
public:
    LeftMissle(Compoment* sc) {
        craft = sc;
    }
    void Fire(){
        craft->Fire();
        cout<<"Left missle:xxxxxx"<<endl;
    }
};


class RightMissle  :public Compoment {
    Compoment* craft;
public:
    RightMissle(Compoment* sc) {
        craft = sc;
    }
    void Fire(){
        craft->Fire();
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



