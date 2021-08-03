#include<iostream>
#include<queue>
using namespace std;

struct Node
{    
    int key;
    Node* left;
    Node* right;
};
//1
Node* createNode(int data)
{
    Node* k = new Node;
    k->key= data;
    k->left = k->right = NULL;
    return k;
}
//2
void Insert(Node* &root, int x)
{
    if(root == NULL)
    {
        root = createNode(x);
        return ;
    }
    if(root->key == x)
    {
        return ;
    }
    if(root->key > x)
    {
        Insert(root->right,x);
        return ;
    }
    if(root->key < x)
    {
        Insert(root->left,x);
        return ;
    }
}
//3
void NLR(Node* root)
{
    if(root == NULL)
        return;
    cout<<root->key;
    NLR(root->left);
    NLR(root->right);
}
//4
void LNR(Node* root)
{
    if(root == NULL)
        return ;
    LNR(root->left);
    cout<<root->key;
    LNR(root->right);
}
//5
void LRN(Node* root)
{
    if(root == NULL)
        return ;
    LNR(root->left);
    LNR(root->right);
    cout<<root->key;
}
//6 
void LevelOrder(Node* root)
{
    if (root == NULL)
        return;
    queue<Node*> q;
    q.push(root);
    while(!q.empty())
    {
        Node* p = q.front();
        cout << p->key << " ";
        if(p->left != NULL)
        {
            q.push(p->left);
        }
        if(p->right != NULL)
        {
            q.push(p->right);
        }
        q.pop();
    }
}
//7
int Height(Node * root)
{
    if(root == NULL)
        return 0;
    return max(Height(root->left),Height(root->right)) + 1;
}
//8
int countNode(Node* root)
{
    if(root == NULL)
        return 0;
    return countNode(root->left) + countNode(root->right) + 1;
}
//9
int sumNode(Node* root)
{
    if(root == NULL)
        return 0;
    return sumNode(root->left) + sumNode(root->right) + root->key;
}
//10
Node* Search(Node* root , int x)
{
    if(root == NULL)
        return NULL;
    if(root->key > x)
    {
        return Search(root->left,x);
    }
    if(root->key<x)
    {
        return Search(root->right,x);
    }
    return root;
}
//11
void Remove(Node* &root, int x)
{
    if(root == NULL)
    {
        return;
    }
    if(root->key>x)
        Remove(root->left,x);
    if (root->key < x)
    {
        Remove(root->right,x);
    }
    if(root->key == x)
    {
        if(root->left == NULL && root->right == NULL)
        {
            // Trường hợp Node có 0 con
            delete root;
            root = NULL;
            return;
        }
        if(root->left != NULL && root->right == NULL)
        {
            // Trường hợp Node chỉ có con bên trái
           Node* temp = root;
           root = root->left;
           delete temp;
           return;
        }
        if(root->left == NULL && root->right != NULL)
        {
            // Trường hợp Node chỉ có con bên phải
            Node* temp = root;
            root = root->right;
            delete temp;
            return;
        }
        if(root->left != NULL && root->right != NULL)
        {
            // Trường hợp Node có 2 con
            Node* p =root->right;
            while (p->left !=NULL)
            {
                p=p->left;// Tìm Node trái nhất của con cây bên phải
            }
            root->key = p->key;
            Remove(root->right,root->key);
            return;
        }
    }
}

//12
Node* createTree(int a[],int n)
{
    Node* root = NULL;
    for (int  i = 0; i < n; i++)
    {
        Insert(root,a[i]);
    }
    return root;
}
//13
void RemoveTree(Node* &root)
{
    if(root == NULL)
    {
        return;
    }
    while (root != NULL)
    {
        Remove(root,root->key);
    }
}
//14
int heightNode(Node* root, int val)
{
    if(root == NULL)
    {
        return 0;
    }
    if(root->key > val)
        return heightNode(root->left,val);
    if(root->key < val)
        return heightNode(root->right,val);
    return Height(root);
}
//15
int Level(Node* root,Node* p)
{
    if(root == NULL)
    {
        return 0;
    }
   queue<Node*> q1;
   queue<int> q2;
   q1.push(root);
   q2.push(1);
   while (!q1.empty())
   {
       Node* temp = q1.front();
       q1.pop();
       int level = q2.front();
       q2.pop();
       if(temp == p)
       {
           return level;
       }
       if(temp->left != NULL)
       {
           q1.push(temp->left);
           q2.push(level+1);
       }
       if(temp->right != NULL)
       {
           q1.push(temp->right);
           q2.push(level+1);
       }
   }
   return 0;
}
//16
int countLeaf(Node* root)
{
    if(root == NULL)
    {
        return 0;
    }
    if(root->left == NULL && root->right == NULL)
    {
        return 1;
    }
    return countLeaf(root->left) + countLeaf(root->right);
}
//17
int countLess(Node* root, int x)
{
    if (root == NULL)
        return 0;
    if (root->key > x)
    {
        return countLess(root->left, x);
    }
    if (root->key == x)
    {
        return countNode(root->left);
    }
    return countLess(root->right, x) + countNode(root->left) + 1;
}
//18
int countGreater(Node* root, int x)
{
    if (root == NULL)
        return 0;
    if (root->key < x)
    {
        return countLess(root->right, x);
    }
    if (root->key == x)
    {
        return countNode(root->right);
    }
    return countLess(root->left, x) + countNode(root->right) + 1;
}
//19 
int minNode(Node* root)
{
    if(root == NULL)
        return 1000000;
    return min(root->key,min(minNode(root->left),minNode(root->right)));
}
int maxNode(Node* root)
{
    if(root == NULL)
        return -1000000;
    return max(root->key,max(maxNode(root->left),maxNode(root->right)));
}
bool isBST(Node* root)
{
    if(root == NULL)
    {
        return true;
    }
    if(root->key > minNode(root->right) && root->key > maxNode(root->left))
    {
        return isBST(root->left) && isBST(root->right);
    }
    return false;
}
//20
bool isFULLBST(Node* root)
{
    if(root == NULL)
        return true;
    if(root->left == NULL && root->right == NULL)
        return false;
    if(root->left != NULL && root->right != NULL)
    {
        return isBST(root) && isFULLBST(root->left) && isFULLBST(root->right);
    }
    return false;
}

int main(int argc,char* argv[])
{
    int a[20];
    for (int i = 0; i < argc - 2; i++)
    {
        a[i] = stoi(argv[2 + i]);
        cout<<a[i]<<" ";
    }
    cout<<endl;
    Node* root = NULL;
    root = createTree(a, argc-2);
    LevelOrder(root);
    cout << endl;
    //Remove(root, findMax(root));
    LevelOrder(root);
    return 0;
}