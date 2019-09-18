#include <iostream>
#include <vector>

using namespace std;

class subject;

struct IGraph {
    virtual void update(subject*)=0;
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

    void notify(){
        for(auto p : v ) {
            p->update(this);
        }
    }

};



class Table : public subject {
    int data;
    vector<IGraph*> v;
public:

    int GetData() {
        return data;
    }

    void SetData(int d){
        data = d;
        notify();
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

    void update(subject* p) {
        //int n = p->getData();
        int n = static_cast<Table*>(p)->GetData();
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

    void update(subject* p) {
        //int n = p->getData();
        int n = static_cast<Table*>(p)->GetData();
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


