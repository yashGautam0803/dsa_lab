#include<bits/stdc++.h>
using namespace std;
int op(string op, int a, int b)
{
    if(op=="+")
        return a+b;
    else if(op=="-")
        return a-b;
    else if(op=="*")
        return a*b;
    else
    {
        if(b==0)
            return -1;
        return a/b;
    }
}
int evalpostfix(string s)
{
    int res=0;
    stack<int> st;
    stringstream ss(s);
    string temp;
    while(ss>>temp)
    {
        if(temp!="+" && temp!="-" && temp!="*" && temp!="/")
        {
            st.push(stoi(temp));
        }
        else
        {
            if(st.size()>2)
                return INT_MIN;
            int op2=st.top();
            st.pop();
            int op1=st.top();
            st.pop();
            res=op(temp,op1,op2);
            st.push(res);
        }
    }
    if(st.size()>1)
        return INT_MIN;
    return st.top();
}
int main()
{
    cout<<"Enter a postfix expression with operands and operators separated by a space: ";
    string s;
    getline(cin,s);
    int val=evalpostfix(s);
    if(val==-1){cout<<"\nInvalid expression";}
    else {cout<<"\nevaluated value is: "<<val;}{}
    return 0;
}