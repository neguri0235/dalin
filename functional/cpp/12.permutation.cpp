#include <iostream>

using namespace std;


void doPermute( const string& chosen, const string& remaining)
{
    if(remaining == ""){
        cout<<chosen<<endl;
    }else{

        for(int u = 0; u<remaining.length(); ++u) {
            doPermute(chosen+remaining[u], remaining.substr(0,u)+remaining.substr(u+1));
        }
    }
}

void permute(const string& s)
{
    doPermute("",s);
}


auto main()-> int
{
    string str;
    getline(cin,str);
    permute(str);
    return 0;
}
