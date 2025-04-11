#include<bits/stdc++.h>
using namespace std;
class Node
{
    public:
        int data;
        Node* prev;
        Node* next;
        Node(int data)
        {
            this->data=data;
            next=prev=nullptr;
        }
};
class DoublyLL{
    public:
        Node* head=nullptr;
        void insert(int data)
        {
            Node* newnode=new Node(data);
            if(!head)
            {
                head=newnode;
                return;
            }
            Node* temp=head;
            while(temp->next)
            {
                temp=temp->next;
            }
            temp->next=newnode;
            newnode->prev=temp;
        }
        void insert_in_between(int data, int pos)
        {
            Node* newnode=new Node(data);
            if(!head || pos==1)
            {
                newnode->next=head;
                if(head) head->prev=newnode;
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
            newnode->prev=temp;
            if(temp->next)
                temp->next->prev=newnode;
            temp->next=newnode;
        }
        void sort()
        {
            if(!head)
            {
                cout<<"\nEmpty";
                return;
            }
            Node *i, *j;
            for(i=head;i!=nullptr;i=i->next)
            {
                for(j=head;j->next!=nullptr;j=j->next)
                {
                    if(j->data>j->next->data)
                    {
                        swap(j->data, j->next->data);
                    }
                }
            }
        }
        void reverse()
        {
            if(!head) return;
            Node* curr=head, *temp=nullptr;
            while(curr!=nullptr)
            {
                temp=curr->prev;
                curr->prev=curr->next;
                curr->next=temp;
                curr=curr->prev;
            }
            if(temp)
                head=temp->prev;
        }
        void insert_in_rightful_place(int data)
        {
            Node *newnode=new Node(data);
            if(!head ||head->data>=data)
            {
                newnode->next=head;
                if(head) head->prev=newnode;
                head=newnode;
                return;
            }
            Node* temp=head;
            while(temp->next && temp->next->data<data)
            {
                temp=temp->next;
            }
            newnode->next=temp->next;
            newnode->prev=temp;
            if(temp->next) temp->next->prev=newnode;
            temp->next=newnode;
        }
        void Delete(int pos)
        {
            if(!head) return;
            Node* temp=head;
            if(pos==1)
            {
                head=head->next;
                delete temp;
                return;
            }
            int i=1;
            while(temp && i++<pos)
            {
                temp=temp->next;
            }
            if(!temp) return;
            if(temp->prev)
                temp->prev->next=temp->next;
            if(temp->next)
                temp->next->prev=temp->prev;
            delete temp;
        }
        void search(int data)
        {
            Node* temp=head;
            int count=0;
            int flag=0;
            while(temp && flag==0)
            {
                count++;
                if(temp->data==data) flag=1;
                else temp=temp->next;
            }
            if(flag) cout<<"\nFount at: "<<count<<endl;
        }
        void print()
        {
            if(!head) return;
            Node* temp=head;
            cout<<"\n";
            while(temp)
            {
                cout<<temp->data<<"<->";
                temp=temp->next;
            }
            cout<<"NULL";
        }
};
int main()
{
    DoublyLL l;
    l.insert_in_rightful_place(2);
    l.insert_in_rightful_place(4);
    l.insert_in_rightful_place(1);
    l.print();
    l.insert(9);
    l.insert(0);
    l.insert(8);
    l.print();
    l.sort();
    l.print();
    l.reverse();
    l.print();
    l.search(9);
    l.insert_in_between(7, 2);
    l.print();
    l.Delete(4);
    l.print();
    return 0;
}