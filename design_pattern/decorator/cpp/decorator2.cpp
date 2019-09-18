#include <iostream>

using namespace std;

class SpaceCraft {
    int color;
    int speed;
public:
    void Fire() {
    cout<<"Space craft:-----"<<endl;
   }

};

class LeftMissle {
    SpaceCraft* craft;
public:
    LeftMissle(SpaceCraft* sc) {
        craft = sc;
    }
    void Fire(){
        craft->Fire();
        cout<<"Left missle:xxxxxx"<<endl;
    }
};


class RightMissle {
    SpaceCraft* craft;
public:
    RightMissle(SpaceCraft* sc) {
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
    lm.Fire();

    return 0;
}


