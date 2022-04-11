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
        B->Up = NULL;
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
        B->Up = NULL;
    }
}

void printBT(const string &prefix, const tree *node, bool isLeft)
{
    if (node != nullptr)
    {
        cout << prefix;
        cout << (isLeft ? "|--" : "L--");
        cout << "(" << node->val << ")" << endl;
        printBT(prefix + (isLeft ? "|   " : "    "), node->R, true);
        printBT(prefix + (isLeft ? "|   " : "    "), node->L, false);
    }
}

void printBT(const tree *node)
{
    printBT("", node, false);
}

tree *Minimum(tree *root)
{
    if (root != NULL)
    {
        tree *p = root;
        while (p->L)
            p = p->L;
        return p;
    }
}

tree *Maximum(tree *root)
{
    if (root != NULL)
    {
        tree *p = root;
        while (p->R)
            p = p->R;
        return p;
    }
}

tree *After(tree *root)
{
    if (root != NULL)
    {
        if (root->R)
            return Minimum(root->R);
        else
        {
            tree *p = root;
            if (p->Up->L == p)
            {
                return p->Up;
            }

            else if (p->Up->R == p)
            {
                while (p->Up->R == p)
                {
                    p = p->Up;
                    if (p->Up == NULL)
                    {
                        return NULL;
                    }
                }
                return p->Up;
            }
        }
    }
}

tree *Before(tree *root)
{
    if (root != NULL)
    {
        if (root->L)
            return Maximum(root->L);
        else
        {
            tree *p = root;
            if (p->Up->R == p)
            {
                return p->Up;
            }

            else if (p->Up->L == p)
            {
                while (p->Up->L == p)
                {
                    p = p->Up;
                    if (p->Up == NULL)
                    {
                        return NULL;
                    }
                }
                return p->Up;
            }
        }
    }
}

void Delete(tree *root)
{
    if (root != NULL)
    {
        if (root->L && root->R)
        {
            tree *after_root = After(root);
            if (root->R != after_root)
            {
                if (after_root->L || after_root->R)
                    if (after_root->R)
                    {
                        after_root->R->Up = after_root->Up;
                        after_root->Up->L = after_root->R;
                    }
                    else if (after_root->Up->L == after_root)
                        after_root->Up->L = NULL;

                after_root->L = root->L;
                after_root->L->Up = after_root;
                after_root->R = root->R;
                after_root->R->Up = after_root;
                after_root->Up = root->Up;

                if (root->Up->L == root)
                    root->Up->L = after_root;

                else
                    root->Up->R = after_root;
            }
            else
            {
                if (root->Up->R == root)
                    root->Up->R = after_root;
                else
                    root->Up->L = after_root;
                after_root->L = root->L;
            }
        }
        else if (root->L || root->R)
        {
            tree *kid = root->L;
            if (root->R)
                kid = root->R;
            if (root->Up->L == root)
                root->Up->L = kid;
            else
                root->Up->R = kid;
        }
        else
        {
            if (root->Up->L == root)
                root->Up->L = NULL;
            else
                root->Up->R = NULL;
        }
        delete root;
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

    int tree_value[18] = {10, 20, 15, 25, 17, 13, 30, -12, -7, -9, -8, -10, -5, -6, -2, -20, -15, -13};
    for (int i = 0; i < 18; i++)
    {
        Insert(root, tree_value[i]);
    }
    // cout<<root->val<<endl<<root->R->val<<endl<<root->L->val<<endl<<root->R->L->val;
    // printBT(root);
    // RotateRightUp(root);

    printBT(root);
    tree *input = root->L->R->L;
    cout << "Wartosc: " << input->val << endl;
    Delete(input);
    printBT(root);
    // InOrder(root);

    return 0;
}
