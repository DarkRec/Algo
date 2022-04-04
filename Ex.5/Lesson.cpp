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

tree *Search(tree *&root, int x)
{
    if (root != NULL)
    {
        if (root->val < x)
            return Search(root->R, x);
        else if (root->val > x)
            return Search(root->L, x);
        else if (root->val == x)
        {
            return root;
        }
    }
    return root;
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

int main()
{
    tree *root = NULL;
    Insert(root, 3);
    Insert(root, 8);
    Insert(root, 5);
    Insert(root, -6);
    Insert(root, 4);
    // cout<<root->val<<endl<<root->R->val<<endl<<root->L->val<<endl<<root->R->L->val;
    InOrder(root);
    printBT(root);
    tree *e = Search(root, 8);
    cout << e->val;
    return 0;
}
