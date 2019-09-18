#include <iostream>
#include <vector>

using namespace std;

struct IGraph {
    virtual void update(int)=0;
    virtual ~IGraph(){}
};




class Table {
    int data;
    vector<IGraph*> v;
public:
    void attach(IGraph* p) {
        v.push_back(p);
    }
    void detach(IGraph* p) {}


    void SetData(int d){
        data = d;
        for(auto p : v ) {
            p->update(data);
        }
    }

};


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

