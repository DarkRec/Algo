#include <iostream>

using namespace std;

struct tree
{
    int val;
    tree *R;
    tree *L;
};

void Insert(tree *&root, int x)
{
    if (root == NULL)
    {
        tree *p = new tree;
        p->L = p->R = NULL;
        p->val = x;
        root = p;
    }
    else
    {
        if (root->val <= x)
            Insert(root->R, x);
        else
            Insert(root->L, x);
    }
}

void printBT(const string &prefix, const tree *node, bool isLeft)
{
    if (node != nullptr)
    {
        cout << prefix;
        cout << (isLeft ? "|--" : "L--");
        cout << node->val << endl;
        printBT(prefix + (isLeft ? "|   " : "    "), node->R, true);
        printBT(prefix + (isLeft ? "|   " : "    "), node->L, false);
    }
}

void printBT(const tree *node)
{
    printBT("", node, false);
}

void RotateRight(tree *&root)
{
    tree *A = root;
    tree *B = NULL;
    tree *BR = NULL;
    if (root->L)
    {
        B = root->L;
        if (root->L->R)
            BR = root->L->R;
        B->R = A;
        A->L = BR;
        root = B;
    }
}

void RotateLeft(tree *&root)
{
    tree *A = root;
    tree *B = NULL;
    tree *BL = NULL;
    if (root->R)
    {
        B = root->R;
        if (root->R->L)
            BL = root->R->L;
        B->L = A;
        A->R = BL;
        root = B;
    }
}

void InOrder(tree *&root)
{
    if (root != NULL)
    {
        if (root->L != NULL)
            InOrder(root->L);
        cout << root->val << endl;
        if (root->R != NULL)
            InOrder(root->R);
    }
}

int main()
{
    tree *root = NULL;
    Insert(root, 5);
    Insert(root, 2);
    Insert(root, 1);
    Insert(root, 3);
    Insert(root, 4);
    Insert(root, 6);
    Insert(root, 5);
    Insert(root, 8);
    Insert(root, 7);
    // cout<<root->val<<endl<<root->R->val<<endl<<root->L->val<<endl<<root->R->L->val;
    RotateRight(root);
    printBT(root);
    RotateLeft(root);
    // InOrder(root);
    return 0;
}
