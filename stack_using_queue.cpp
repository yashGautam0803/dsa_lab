#include<bits/stdc++.h>
using namespace std;
class Stack
{
    queue<int> q;
    public:
        void push(int data)
        {
            q.push(data);
            int size=q.size();
            while(size>1)
            {
                q.push(q.front());
                q.pop();
                size--;
            }
        }
        void pop()
        {
            if(!q.empty())
                q.pop();
            else
                cout<<"Stack is empty\n";
        }
        void Top()
        {
            if(!q.empty())
                cout<<q.front()<<" is the top element\n";
            else return;
        }
        bool empty()
        {
            return q.empty();
        }
        void display()
        {
            if(q.empty()) return;
            queue<int> temp=q;
            cout<<"Stack:-\n";
            while(!temp.empty())
            {
                cout<<"|"<<temp.front()<<"|"<<"\n---\n";
                temp.pop();
            }
            cout<<endl;
        }
};
int main()
{
    Stack s;
    s.push(9);
    s.push(0);
    s.push(8);
    s.push(2);
    s.display();
    s.pop();
    s.Top();
    return 0;
}