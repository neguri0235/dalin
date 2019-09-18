// 컨테이너 어댑터

#include <iostream>
#include <list>
#include <vector>
#include <deque>
using namespace std;

/* 방법 1
template<typename T>class stack  public list<T>
{
public:
    void push(const T& a){
        list<T>::push_back(a);

    }

    void pop(){
        list<T>::pop_back();

    }

    T& top(){
        return list<T>::back();
    }
};

int main()
{

    stack<int> s;
    s.push(10);
    s.push(20);

    cout<<s.top()<<endl;

    return 0;
}
*/


/* 방법 2
template<typename T>class stack // : public list<T>
{
    //
    //list<T> st;
    vector<T> st;
public:
    void push(const T& a){
        //list<T>::push_back(a);
        st.push_back(a);
    }

    void pop(){
        //list<T>::pop_back();
        st.pop_back();
    }

    T& top(){
//return list<T>::back();
        return st.back();
    }
};

int main()
{

    stack<int> s;
    s.push(10);
    s.push(20);

    cout<<s.top()<<endl;

    return 0;
}
*/

// 방법 3
template<typename T, typename C = deque<T>>class stack // : public list<T>
{

    C st;
public:
    void push(const T& a){
        //list<T>::push_back(a);
        st.push_back(a);
    }

    void pop(){
        //list<T>::pop_back();
        st.pop_back();
    }

    T& top(){
//return list<T>::back();
        return st.back();
    }
};

int main()
{

    stack<int, vector<int>> s;
    s.push(10);
    s.push(20);

    cout<<s.top()<<endl;

    return 0;
}
