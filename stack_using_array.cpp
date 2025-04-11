#include<bits/stdc++.h>
using namespace std;
class Stack
{
        int size;
        int *arr;
        int top;
        public:
            Stack()
            {
                arr=new int(size);
                top=-1;
                size=1000;
            }
            void Print(int n)
            {
                cout<<"Stack looks like this:-"<<endl<<endl;
                for(int i=n-1;i>=0;i--)
                {
                    cout<<"|"<<arr[i]<<"|";
                    cout<<endl<<"---"<<endl;
                }
            }
            void push(int data)
            {
                top++;
                arr[top]=data;
            }
            int pop()
            {
                int popped=arr[top];
                top--;
                return popped;
            }
            int Top()
            {
                return arr[top];
            }
            int Size()
            {
                return top+1;
            }
};
int main()
{
    Stack s;
    s.push(5);
    s.push(4);
    s.push(6);
    s.push(0);
    int n=s.Size();
    s.Print(n);
    cout<<"\nSize: "<<n;
    cout<<"\n"<<s.pop()<<" is popped";
    cout<<"\nnew size: "<<s.Size();
    cout<<"\nTop element: "<<s.Top();
    return 0;
}