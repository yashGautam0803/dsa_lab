#include<bits/stdc++.h>
using namespace std;
class Node
{
    public:
        int key;
        Node *left, *right;
        Node(int key)
        {
            this->key=key;
            left=right=nullptr;
        }
};
class BST
{
    public:
        Node* insertNode(Node* root, int key)
        {
            if(!root)
                return new Node(key);
            if(root->key==key)
                return root;
            if(key<root->key)
                root->left=insertNode(root->left, key);
            else
                root->right=insertNode(root->right, key);
            return root;
        }
        void inOrder(Node* root)
        {
            if(!root) return;
            inOrder(root->left);
            cout<<root->key<<" ";
            inOrder(root->right);
        }
        void preOrder(Node* root)
        {
            if(!root) return;
            cout<<root->key<<" ";
            preOrder(root->left);
            preOrder(root->right);
        }
        void postOrder(Node* root)
        {
            if(!root) return;
            postOrder(root->left);
            postOrder(root->right);
            cout<<root->key<<" ";
        }
        int getDepth(Node* root, int key, int depth)
        {
            if(!root)
                return -1;
            if(root->key==key)
                return depth;
            if(key<root->key)
                return getDepth(root->left,key,depth+1);
            else
                return getDepth(root->right,key,depth+1);    
        }
        int getheight(Node* root)
        {
            if(!root) return 0;
            int lh=getheight(root->left);
            int rh=getheight(root->right);
            return 1+max(rh,lh);
        }
        int findMIN(Node* root)
        {
            Node* temp=root;
            if(!root) return -1;
            while(temp->left)
                temp=temp->left;
            return temp->key;
        }
        int findMAX(Node* root)
        {
            Node* temp=root;
            if(!root) return -1;
            while(temp->right)
                temp=temp->right;
            return temp->key;
        }
        void levelOrder(Node* root)
        {
            if(!root) return;
            queue<Node*> q;
            q.push(root);
            while(!q.empty())
            {
                Node* current=q.front();
                q.pop();
                cout<<current->key<<" ";
                if(current->left)
                    q.push(current->left);
                if(current->right)
                    q.push(current->right);
            }
        }
};
int main()
{
    BST obj;
    Node* root=nullptr;
    int ch;
    root=obj.insertNode(root,4);
    root=obj.insertNode(root,3);
    root=obj.insertNode(root,6);
    root=obj.insertNode(root,2);
    root=obj.insertNode(root,5);
    root=obj.insertNode(root,7);
    cout<<"\nheight: "<<obj.getheight(root);
    cout<<"\nDepth of 3 is: "<<obj.getDepth(root,3,0);
    cout<<endl;
    obj.inOrder(root);
    cout<<endl;
    obj.preOrder(root);
    cout<<endl;
    obj.postOrder(root);
    cout<<"\n max: "<<obj.findMAX(root);
    cout<<"\n min: "<<obj.findMIN(root);
    return 0;
}