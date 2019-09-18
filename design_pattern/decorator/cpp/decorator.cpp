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

class LeftMissle : public SpaceCraft {
public:
    void Fire(){
        SpaceCraft::Fire();
        cout<<"Left missle:xxxxxx"<<endl;
    }
};

int main()
{
    SpaceCraft sc;
    sc.Fire();
    LeftMissle lm;
    lm.Fire();
    return 0;
}
