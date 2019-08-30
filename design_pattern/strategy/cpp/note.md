### strategy pattern

* 실행 시간에 정책을 변경.
* 유연성이 좋지만, 대신 가상함수 호출에 대한 오버헤드가 있음.

``` cpp
struct ISync {
    virtual void lock(){}
    virtual void unlock(){}
    virtual~ISync(){}
};

class mutex  : public ISync{
public:
    virtual void lock(){
        cout<<"MUTEX LOCK"<<endl;
    }
    virtual void unlock(){
        cout<<"MUTEX UNLOCK"<<endl;
    }
};

class nomutex : public ISync {
public:
    virtual void lock(){
        cout<<"MUTEX NO LOCK"<<endl;
    }
    virtual void unlock(){
        cout<<"MUTEX NO UNLOCK"<<endl;
    }
};

template<typename T> class List {
    ISync * psync = nullptr;
public:
    void setSync(ISync* p) { psync= p;}
    void push_front(const T& a) {
        if(psync != nullptr) psync->lock();
        if(psync != nullptr) psync->unlock();
    }
};

List<int> s;
int main()
{
    nomutex nmtx;
    s.setSync(&nmtx);
    s.push_front(10);
    return 0;
}
```


### Policy base design

C++ 에서 사용하는 기법, strategy 사용하면 가상함수의 오버헤드가 있으므로  
inline 치환할 수 있는 template 을 사용하도록 함.

``` cpp
struct ISync {
    virtual void lock(){}
    virtual void unlock(){}
    virtual~ISync(){}
};

class mutex{
public:
    inline void lock(){
        cout<<"MUTEX LOCK"<<endl;
    }
    inline void unlock(){
        cout<<"MUTEX UNLOCK"<<endl;
    }
};

class nomutex {
public:
    inline void lock(){
        cout<<"MUTEX NO LOCK"<<endl;
    }

    inline void unlock(){
        cout<<"MUTEX NO UNLOCK"<<endl;
    }
};

template<typename T, typename ThreadModel = nomutex> class List {
    ThreadModel tm;
public:

    void push_front(const T& a) {
        tm.lock();
        tm.unlock();
    }
};

int main()
{

    List<int> s;
    s.push_front(10);
    return 0;
}
```