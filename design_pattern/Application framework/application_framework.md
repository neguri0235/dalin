응용프로그램의 흐름을 미리 정의 한것  

1. CWinApp에서 파생된 클래스를 설계하고
2. Init(), Exit(), Run()에서 가상함수를 제공하면, 각 단계에서 할 일을 만듬
3. 마지막으로 사용자가 만든 객체를 전역적으로 한개 생성

application framework의 기본적인 형태임

``` cpp
class CWinApp;

CWinApp* g_app = nullptr;

class CWinApp {
public:
    CWinApp() {g_app = this;}
    virtual bool Init(){ return false;}
    virtual int Exit() {return false;}
    virtual int Run()  {return false;}
};

int main()
{
    if(g_app->Init() == true) {
        g_app->Run();
    }

    g_app->Exit();
    cout<<"main"<<endl;
    return 0;
}


class MyApp : public CWinApp {
public:
    virtual bool Init() {
        cout<<"init"<<endl;
        return true;
    }

    virtual int Exit() {
        cout<<"finished"<<endl;
        return false;
    }

    virtual int Run()  {return false;}
};

MyApp theApp;
```

