#include <iostream>
#include <vector>

using namespace std;

struct IGraph {
    virtual void update(int)=0;
    virtual ~IGraph(){}
};


class subject {
public:
    vector<IGraph*>v;
public:
    void attach(IGraph* p) {
        v.push_back(p);
    }
    void detach(IGraph* p) {}

    void notify(int data){
        for(auto p : v ) {
            p->update(data);
        }
    }

};



class Table : public subject {
    int data;
    vector<IGraph*> v;
public:


    void SetData(int d){
        data = d;
        notify(d);
    }

};
/*
class Table3D : public subject {
    int data[10];
public:


    void SetData(int d){
        data = d;
        notify(data);

    }

};
*/
class PieGraph : public IGraph {
public:
    void Draw(int n) {
        cout<<"Pie graph"<<endl;
        for(int i = 0; i<n; i++){
            cout<<'*';
        }
        cout<<endl;
    }

    void update(int n) {
        Draw(n);
    }
};

class BarGraph : public IGraph {
public:
    void Draw(int n) {
        cout<<"Bar graph"<<endl;
        for(int i = 0; i<n; i++){
            cout<<'-';
        }
        cout<<endl;
    }

    void update(int n) {
        Draw(n);
    }
};


int main()
{
    BarGraph bar;
    PieGraph pie;

    Table t;
    t.attach(&bar);
    t.attach(&pie);
    t.SetData(10);

    return 0;
}

