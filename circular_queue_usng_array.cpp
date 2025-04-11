#include<bits/stdc++.h>
using namespace std;
class Queue
{
    int start, end, currsize, maxsize;
    int *arr;
    public:
        Queue(int maxsize)
        {
            arr=new int[maxsize];
            this->maxsize=maxsize;
            start=-1;
            end=-1;
            currsize=0;
        }
        void push(int data)
        {
            if(currsize==maxsize){cout<<"Queue is full\n"; return;}
            if(end==-1)
            {
                start=0;
                end=0;
            }
            else
                end=(end+1)%maxsize;
            arr[end]=data;
            currsize++;
            cout<<"The element pushed is: "<<data<<endl;
        }
        void pop()
        {
            if(start==-1)
            {cout<<"Queue is empty\n"; return;}
            cout<<"popped element: "<<arr[start]<<endl;
            if(currsize==1)
            {
                start=-1;
                end=-1;
            }
            else
                start=(start+1)%maxsize;
            currsize--;
        }
        void Front()
        {
            if(start==-1) return;
            cout<<"front element is: "<<arr[start]<<endl;
        }
        void size()
        {
            cout<<"Current size: "<<currsize<<endl;
        }
};
int main()
{
    Queue q(4);
    q.push(4);
    q.push(0);
    q.push(1);
    q.push(8);
    q.pop();
    q.push(3);
    q.size();
    q.Front();
    return 0;
}