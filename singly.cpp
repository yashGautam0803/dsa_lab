#include<bits/stdc++.h>
using namespace std;
class Node
{
    public:
        int data;
        Node *next;
        Node(int data)
        {
            this->data=data;
            next=nullptr;
        }
};
class LinkedList
{
    Node *head=nullptr;
    public:
        void insert(int data)
        {
            Node *newnode=new Node(data);
            if(!head)
            {
                head=newnode;
                return;
            }
            Node *temp=head;
            while(temp->next)
            {
                temp=temp->next;
            }
            temp->next=newnode;
        }
        void insertinbetween(int data,int pos)
        {
            Node *newnode=new Node(data);
            if(!head)
            {
                head=newnode;
                return;
            }
            int i=1;
            Node* temp=head;
            while(temp->next && i++<pos-1)
            {
                temp=temp->next;
            }
            newnode->next=temp->next;
            temp->next=newnode;
        }
        void sort()
        {
            if(!head)
            {
                cout<<"Empty linked list\n";
                return;
            }
            Node *i, *j;
            for(i=head;i!=nullptr;i=i->next)
            {
                for(j=head;j->next!=nullptr;j=j->next)
                {
                    if(j->data>j->next->data)
                    {
                        swap(j->data,j->next->data);
                    }
                }
            }
        }
        void reverse()
        {
            if(!head)
                return;
            Node *curr=head;
            Node *prev=nullptr;
            Node *next=nullptr;
            while(curr!=nullptr)
            {
                next=curr->next;
                curr->next=prev;
                prev=curr;
                curr=next;
            }
            head=prev;
        }
        void insert_in_rightful_place(int data)
        {
            Node *newnode=new Node(data);
            if(head==nullptr || head->data>=data)
            {
                newnode->next=head;
                head=newnode;
                return;
            }
            Node* temp=head;
            while(temp->next!=nullptr && temp->next->data<data)
            {
                temp=temp->next;
            }
            newnode->next=temp->next;
            temp->next=newnode;
        }
        void Delete(int pos)
        {
            Node* temp=head;
            Node* prev=nullptr;
            if(pos==1)
            {
                head=head->next;
                delete temp;
                return;
            }
            int i=1;
            while(temp->next!=nullptr && i++<pos)
            {
                prev=temp;
                temp=temp->next;
            }
            prev->next=temp->next;
            delete temp;
        }
        void search(int data)
        {
            Node* temp=head;
            int count=0;
            int flag=0;
            while(temp!=nullptr && flag==0)
            {
                if(temp->data==data)
                    flag=1;
                temp=temp->next;
                count++;
            }
            if(flag)
                cout<<"\nfound at: "<<count<<endl;
            else
                return;
        }
        void print()
        {
            if(!head)
            {
                cout<<"\nEmpty\n";
                return;
            }
            Node* temp=head;
            while(temp)
            {
                cout<<temp->data<<"->";
                temp=temp->next;
            }
            cout<<"NULL";
        }
        void hasCycle()
        {
            Node* slow=head;
            Node* fast=head;
            while(fast && fast->next)
            {
                slow=slow->next;
                fast=fast->next->next;
                if(slow==fast)
                    cout<<"\ncycle found";
            }
            cout<<"\ncycle not found";
        }
        void findmiddle()
        {
            if(!head) return;
            Node* slow=head;
            Node* fast=head;
            while(fast && fast->next)
            {
                slow=slow->next;
                fast=fast->next->next;
            }
            cout<<"Middle: "<<slow->data<<endl;
        }
};
int main()
{
    LinkedList l;
    l.insert_in_rightful_place(2);
    l.insert_in_rightful_place(4);
    l.insert_in_rightful_place(1);
    l.print();
    l.insert(9);
    l.insert(0);
    l.insert(8);
    cout<<endl;
    l.print();
    l.sort();
    cout<<endl;
    l.print();
    l.reverse();
    cout<<endl;
    l.print();
    l.search(9);
    l.insertinbetween(7,2);
    cout<<endl;
    l.print();
    l.Delete(4);
    cout<<endl;
    l.print();
    return 0;
}