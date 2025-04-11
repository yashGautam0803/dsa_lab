#include<bits/stdc++.h>
using namespace std;
class Queue
{
    int size;
    int *arr;
    int front, rear;
    public:
        Queue(int data)
        {
            size=data;
            arr=new int(size);
            front=-1;
            rear=-1;
        }
        void enqueue(int value)
        {
            if(rear==size-1)
            {
                cout<<"Queue is full\n";
                return;
            }
            if(front==-1) front=0;
            rear++;
            arr[rear]=value;
            cout<<"Inserted: "<<value<<endl;
        }
        void dequeue()
        {
            if(front==-1 || front>rear)
            {
                cout<<"Queue is empty\n";
                return;
            }
            cout<<"\ndeleted "<<arr[front++]<<endl;
        }
        void display()
        {
            if(front == -1 || front>rear)
            {
                cout<<"Queue is empty\n";
                return;
            }
            cout<<"QUEUE:\n";
            for(int i=front;i<=rear;i++)
            {
                cout<<"|"<<arr[i];
            }
        }
        void Size()
        {
            cout<<(rear-front)+1<<endl;
        }
};
int main()
{
    Queue q(5);
    q.enqueue(1);
    q.enqueue(4);
    q.enqueue(5);
    q.enqueue(5);
    q.display();
    q.dequeue();
    q.Size();
    q.display();
    return 0;
}