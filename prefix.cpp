#include<bits/stdc++.h>
using namespace std;
int op(string op, int a, int b)
{
    if(op=="+") return a+b;
    else if(op=="-") return a-b;
    else if(op=="*") return a*b;
    else
    { 
        if(b==0) 
            return -1; 
        return a/b;
    }
}
int evalprefix(string s)
{
    stack<int> st;
    int res=0;
    string temp;
    stringstream ss(s);
    while(ss>>temp)
    {
        if(temp!="+" && temp!="-" && temp!="*" && temp!="/")
            st.push(stoi(temp));
        else
        {
            if(st.size()>2)
                return INT_MIN;
            int op1=st.top();
            st.pop();
            int op2=st.top();
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
    cout<<"Enter a prefix expressio with operators and operands separate them with a single space: ";
    string s;
    getline(cin, s);
    stringstream ss(s);
    vector<string> tokens;
    string temp;
    while(ss>>temp)
    {
        tokens.push_back(temp);
    }
    reverse(tokens.begin(), tokens.end());
    s="";
    for(const string& tok: tokens)
    {
        s+=tok+" ";
    }
    s.pop_back();
    int val=evalprefix(s);
    if(val==-1)
        cout<<"\nInvalid expression";
    else
        cout<<"\nEvaluate value: "<<val;
    return 0;
}