#include<bits/stdc++.h>
using namespace std;
class Node
{
    public:
        int data;
        Node* next;
        Node(int data)
        {
            this->data=data;
            next=nullptr;
        }
};
class CircularLL
{
    Node* head=nullptr;
    public:
        void insert(int data)
        {
            Node* newnode=new Node(data);
            if(!head)
            {
                head=newnode;
                newnode->next=head;
                return;
            }
            Node* temp=head;
            while(temp->next!=head)
            {
                temp=temp->next;
            }
            temp->next=newnode;
            newnode->next=head;
        }
        void insert_in_between(int data, int pos)
        {
            Node* newnode=new Node(data);
            if(!head)
            {
                head=newnode;
                newnode->next=head;
                return;
            }
            if(pos==1)
            {
                Node *last=head;
                while(last->next!=head)
                {
                    last=last->next;
                }
                newnode->next=head;
                head=newnode;
                last->next=head;
                return;
            }
            int i=1;
            Node* temp=head;
            while(temp->next!=head && i++<pos-1)
            {
                temp=temp->next;
            }
            newnode->next=temp->next;
            temp->next=newnode;
        }
        void sort()
        {
            if(!head || head->next==head) return;
            Node *i, *j;
            int swapped;
            do
            {
                swapped=0;
                i=head;
                while(i->next!=head)
                {
                    j=i->next;
                    if(i->data>j->data)
                    {
                        swap(i->data,j->data);
                        swapped=1;
                    }
                    i=i->next;
                }
            }while(swapped);
        }
        void reverse()
        {
            if(!head || head->next==head)
                return;
            Node *prev=nullptr;
            Node *next=nullptr;
            Node* curr=head;
            do
            {
                next=curr->next;
                curr->next=prev;
                prev=curr;
                curr=next;
            }while(curr!=head);
            head->next=prev;
            head=prev;
        }
        void insert_in_rightful_place(int data)
        {
            Node* newnode=new Node(data);
            if(!head)
            {
                head=newnode;
                newnode->next=head;
                return;
            }
            if(data<=head->data)
            {
                Node* last=head;
                while(last->next!=head)
                {
                    last=last->next;
                }
                newnode->next=head;
                head=newnode;
                last->next=head;
                return;
            }
            Node* temp=head;
            while(temp->next!=head && temp->next->data<data)
            {
                temp=temp->next;
            }
            newnode->next=temp->next;
            temp->next=newnode;
        }
        void Delete(int pos)
        {
            if(!head) return;
            if(pos==1)
            {
                if(head->next==head)
                {
                    delete head;
                    return;
                }
                Node* last=head;
                while(last->next!=head)
                {
                    last=last->next;
                }
                Node* temp=head;
                head=head->next;
                last->next=head;
                delete temp;
                return;
            }
            Node* temp=head;
            Node* prev=nullptr;
            int i=1;
            while(temp->next!=head && i<pos)
            {
                prev=temp;
                temp=temp->next;
                i++;
            }
            if(i==pos)
            {
                prev->next=temp->next;
                delete temp;
            }
        }
        void search(int data)
        {
            if(!head) return;
            Node* temp=head;
            int count=1;
            do
            {
                if(temp->data==data)
                {
                    cout<<"\nFound at: "<<count;
                    return;
                }
                temp=temp->next;
                count++;
            } while(temp->next!=head);
        }
        void print()
        {
            if(!head) return;
            cout<<"\n";
            Node* temp=head;
            do{
                cout<<temp->data<<"->";
                temp=temp->next;
            }while(temp!=head);
            cout<<head->data;
        }
        int findDistance(int a,int b)
        {
            if(!head) return -1;
            Node* curr=head;
            while(curr->data!=a)
            {
                curr=curr->next;
                if(curr==head) return -1;
            }
            Node* temp=curr;
            int distance=0;
            do
            {
                if(temp->data==b) return distance;
                temp=temp->next;
                distance++;
            }while(temp!=curr);
            if(temp->data!=b) return -1;
            int size=1;
            Node* temp1=head;
            while(temp1->next!=head)
            {
                temp1=temp1->next;
                size++;
            }
            int c=size-distance;
            return min(c,distance);
        }
};
int main()
{
    CircularLL l;
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
    int x=l.findDistance(1,9);
    if(x!=-1)
        cout<<"\nDistnace between 1 and 9: "<<x;
    else cout<<"not found";
    return 0;
}