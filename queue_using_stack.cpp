#include<bits/stdc++.h>
using namespace std;
class Queue
{
    public:
        stack<int> input, output;
        void push(int x)
        {
            cout<<"the element pushed is: "<<x<<endl;
            input.push(x);
        }
        void pop()
        {
            if(output.empty())
            {
                while(input.size())
                {
                    output.push(input.top());
                    input.pop();
                }
                int x=output.top();
                output.pop();
                cout<<x<<" popped\n";
            }
        }
        void top()
        {
            if(output.empty())
            {
                while(input.size())
                {
                    output.push(input.top());
                    input.pop();
                }
            }
            cout<<"top: "<<output.top()<<endl;
        }
        int size()
        {
            return(output.size()+input.size());
        }
};
int main()
{
    Queue q;
    q.push(9);
    q.push(0);
    q.pop();
    q.top();
    return 0;
}