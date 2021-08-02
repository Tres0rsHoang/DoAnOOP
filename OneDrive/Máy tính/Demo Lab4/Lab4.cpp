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
Node * createNode(int data)
{
    Node*p= new Node;
    p->key=data;
    p->left=NULL;
    p->right= NULL;
    return p;
}
//2
void Insert(Node* &pRoot, int x)
{
    if (pRoot == NULL)
    {
        pRoot = createNode(x);
        return;
    }
    if (pRoot->key == x )
    {
        return;
    }
    if(pRoot->key > x)
    {
        Insert(pRoot->left,x);
            return;
    }
    if(pRoot->key < x)
    {
        Insert(pRoot->right , x);
        return ;
    }
}
//3
void NLR(Node* pRoot)
{
    if(pRoot == NULL)
        return;
    cout<< pRoot->key;
    NLR(pRoot->left);
    NLR(pRoot->right);
}
//4
void LNR(Node* pRoot)
{
    if (pRoot == NULL)
        return;
    LNR(pRoot->left);
    cout<<pRoot->key;
    LNR(pRoot->right);
}
//5
void LRN(Node* pRoot)
{
    if (pRoot == NULL)
        return;
    LNR(pRoot->left);
    LNR(pRoot->right);
    cout<<pRoot->key;
}
//6
void LevelOrder(Node* pRoot )
{
    if(pRoot == NULL)
    return ;
    queue<Node*> q;
    q.push(pRoot);
    while (!q.empty() )
    {
        Node* temp = q.front();
        q.pop();
        if(temp->left != NULL)
        {
            q.push(temp->left);
        }
        if(temp->right != NULL)
        {
            q.push(temp->right);
        }
        cout<< temp->key;
    }
}
//7
int Height(Node * pRoot)
{
    if(pRoot == NULL)
        return 0;
    return max(Height(pRoot->left),Height(pRoot->right)) + 1;
}
//8
int countNode(Node* pRoot)
{
    if(pRoot == NULL)
        return 0;
    return countNode(pRoot->left) + countNode(pRoot->right) + 1;
}
//9
int sumNode(Node* pRoot)
{
    if(pRoot == NULL)
    return 0;
    return countNode(pRoot->left) + countNode(pRoot->right) + pRoot->key;
}
//10
Node* Search(Node* pRoot , int x)
{
    if(pRoot == NULL)
        return NULL;
    if(pRoot->key == x)
    {
        return pRoot;
    }
    if(pRoot->key > x)
    {
        return Search(pRoot->left,x);
    }
    if(pRoot->key<x)
    {
        return Search(pRoot->right,x);
    }
}
//11
void Remove(Node* &pRoot, int x)
{
    if(pRoot == NULL)
    {
        return;
    }
    if(pRoot->key>x)
        Remove(pRoot->left,x);
    if (pRoot->key < x)
    {
        Remove(pRoot->right,x);
    }
    if(pRoot->key == x)
    {
        if(pRoot->left == NULL && pRoot->right == NULL)
        {
            // Trường hợp node có 0 con
            delete pRoot;
            pRoot = NULL;
            return;
        }
        if(pRoot->left != NULL && pRoot->right == NULL)
        {
            // Trường hợp node chỉ có con bên trái
           Node* temp = pRoot;
           pRoot = pRoot->left;
           delete temp;
           return;
        }
        if(pRoot->left == NULL && pRoot->right != NULL)
        {
            // Trường hợp node chỉ có con bên phải
            Node* temp = pRoot;
            pRoot = pRoot->right;
            delete temp;
            return;
        }
        if(pRoot->left != NULL && pRoot->right != NULL)
        {
            // Trường hợp node có 2 con
            Node* p =pRoot->right;
            while (p->left !=NULL)
            {
                p=p->left;// Tìm node trái nhất của con cây bên phải
            }
            pRoot->key = p->key;
            Remove(pRoot->right,pRoot->key);
            return;
        }
    }
}

//12
Node* createTree(int a[],int n)
{
    Node* pRoot = NULL;
    for (int  i = 0; i < n; i++)
    {
        Insert(pRoot,a[i]);
    }
    return pRoot;
}
//13
void RemoveTree(Node* &pRoot)
{
    if(pRoot == NULL)
    {
        return;
    }
    while (pRoot != NULL)
    {
        Remove(pRoot,pRoot->key);
    }
}
//14
int heightNode(Node* pRoot, int val)
{
    if(pRoot == NULL)
    {
        return;
    }
    if(pRoot->key > val)
        return heightNode(pRoot->left,val);
    if(pRoot->key < val)
        return heightNode(pRoot->right,val);
    if(pRoot->key == val)
        return Height(pRoot);
}
//15
int Level(Node* pRoot,Node* p)
{
    if(pRoot == NULL)
    {
        return 0;
    }
   queue<Node*> q1;
   queue<int> q2;
   q1.push(pRoot);
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
int countLeaf(Node* pRoot)
{
    if(pRoot == NULL)
    {
        return;
    }
    if(pRoot->left == NULL && pRoot->right == NULL)
    {
        return 1;
    }
    return countLeaf(pRoot->left) + countLeaf(pRoot->right);
}
//17
int countLess(Node* pRoot,int x)
{
    if(pRoot == NULL)
    {
        return;
    }
    if(pRoot->key == x)
        return countNode(pRoot->left);
    if(pRoot->key < x)
    {
        return countNode(pRoot->left)+1+countLess(pRoot->right,x);
    }
    if(pRoot->key > x)
    {
        return countLess(pRoot->left,x);
    }
}
//18
int countGreater(Node* pRoot,int x)
{
    if(pRoot == NULL)
    {
        return;
    }
    if(pRoot->key == x)
        return countNode(pRoot->right);
    if(pRoot->key < x)
    {
        return countNode(pRoot->right)+1+countLess(pRoot->left,x);
    }
    if(pRoot->key > x)
    {
        return countGreater(pRoot->right,x);
    }
}
//19 
int minNode(Node* pRoot)
{
    if(pRoot == NULL)
        return 1000000;
    return min(pRoot->key,min(minNode(pRoot->left),minNode(pRoot->right)));
}
int maxNode(Node* pRoot)
{
    if(pRoot == NULL)
        return -1000000;
    return max(pRoot->key,max(maxNode(pRoot->left),maxNode(pRoot->right)));
}
bool isBST(Node* pRoot)
{
    if(pRoot == NULL)
    {
        return true;
    }
    if(pRoot->key > minNode(pRoot->right) && pRoot->key > maxNode(pRoot->left))
    {
        return isBST(pRoot->left) && isBST(pRoot->right);
    }
    return false;
}
//20
bool isFULLBST(Node* pRoot)
{
    if(pRoot == NULL)
        return true;
    if(pRoot->left == NULL && pRoot->right == NULL)
        return false;
    if(pRoot->left != NULL && pRoot->right != NULL)
    {
        return isBST(pRoot) && isFULLBST(pRoot->left) && isFULLBST(pRoot->right);
    }
    return false;
}
int main()
{
    return 0;
}