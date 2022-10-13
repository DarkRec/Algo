#include <iostream>

using namespace std;

struct tree
{
    int val;
    tree *Up;
    tree *R;
    tree *L;
};

void InsertUp(tree *&root, int x, tree *up)
{
    if (root == NULL)
    {
        tree *p = new tree;
        p->L = p->R = NULL;
        p->val = x;
        p->Up = up;
        root = p;
    }
    else
    {
        if (root->val <= x)
            InsertUp(root->R, x, root);
        else
            InsertUp(root->L, x, root);
    }
}

void Insert(tree *&root, int x)
{
    InsertUp(root, x, root);
}

void RotateRightUp(tree *&root)
{
    tree *A = root;
    tree *B = NULL;
    tree *BR = NULL;
    if (root->L)
    {
        B = root->L;
        if (root->L->R)
        {
            BR = root->L->R;
            BR->Up = A;
        }
        B->R = A;
        A->L = BR;
        A->Up = B;
        root = B;
        B->Up = B;
    }
}

void RotateLeftUp(tree *&root)
{
    tree *A = root;
    tree *B = NULL;
    tree *BL = NULL;
    if (root->R)
    {
        B = root->R;
        if (root->R->L)
        {
            BL = root->R->L;
            BL->Up = A;
        }
        B->L = A;
        A->R = BL;
        root = B;
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

void DeleteLeafs(tree *node)
{
    if (node->R == NULL && node->L == NULL)
    {
        if (node->Up->L == node)
            node->Up->L = NULL;
        else
            node->Up->R = NULL;
    }
    if (node->L != NULL)
        DeleteLeafs(node->L);
    if (node->R != NULL)
        DeleteLeafs(node->R);
}

void SearchTreeAndDelete(tree *&T, int val)
{
    if (T != NULL)
    {
        if (T->val == val)
        {
            while (T->L || T->R)
            {
                DeleteLeafs(T);
            }
        }
        else
        {
            if (T->L)
                SearchTreeAndDelete(T->L, val);
            if (T->R)
                SearchTreeAndDelete(T->R, val);
        }
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
    Insert(root, 7);`
    // cout<<root->val<<endl<<root->R->val<<endl<<root->L->val<<endl<<root->R->L->val;
    // printBT(root);
    // RotateRightUp(root);
    printBT(root);
    SearchTreeAndDelete(root, 6);
    // DeleteLeafs(root);
    cout << endl;
    printBT(root);
    // InOrder(root);
    return 0;
}
