#include <iostream>
#include <fstream>

using namespace std;

class Turn
{
private:
    struct Info
    {
        long long x;
        Info *prev = NULL; 
        Info *next = NULL;
    };
    Info *head;
    Info *tail;
public:
    Turn()
    {
        head = NULL;
        tail = NULL;
    }
    void push(long long x);
    long long top();
    bool isEmpty();
    void pop();
    ~Turn()
    {
        while(!isEmpty())
        {
            Info *p = tail;
            tail = tail -> next;
            delete p;
        }
    }
};

void Turn:: push(long long x)
{
    Info *p = new Info;
    p -> next = NULL;
    p -> x = x;
    if(tail != NULL)
    {
        p -> prev = head;
        head -> next = p;
        head = p;
    }
    else
    {
        p -> prev = NULL;
        head = p;
        tail = p;
    }
}

long long Turn:: top()
{
    return tail -> x;
}

bool Turn:: isEmpty()
{
    return tail ? false : true;
}

void Turn:: pop()
{
    if(!isEmpty())
    {
        Info *p = tail;
        tail = tail -> next;
        delete p;
    }
}

int main()
{
    ifstream fin;
    ofstream fout;
    fin.open("queue.in");
    fout.open("queue.out");
    Turn A;
    int n;
    fin >> n;
    char c;
    long long x;
    for(int i = 0 ; i < n ; i++)
    {
        fin >> c;
        if(c == '+')
        {
            fin >> x;
            A.push(x);
        }
        if(c == '-')
        {
            fout << A.top() << endl;
            A.pop();
        }
    }
    fin.close();
    fout.close();
    return 0;
}
