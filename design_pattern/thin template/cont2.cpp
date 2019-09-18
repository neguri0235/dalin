
#include <iostream>

// template container

using namespace std;

template<typename T>
struct Node {
    T data;
    Node* next;
    Node(T& d, Node* n) :data(d), next(n) {}
};

template<typename T>
class slist {
    Node<T>* head = 0;
public:
    void push_front(T& n) { head = new Node<T>(n, head);}
    T front() { return head->data;}
};

int main()
{
    slist<int> s;
    s.push_front(1);
    s.push_front(2);
    s.push_front(3);

    int n = s.front();

    cout<<n<<endl;
}
