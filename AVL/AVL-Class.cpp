#include <iostream>

using namespace std;

struct tree
{
    int val;
    int bf;
    tree *Up;
    tree *R;
    tree *L;
};

class AVLTree
{
public:
    tree *root;
    AVLTree()
    {
        root = NULL;
    }
    void RR(tree *A);
    void LL(tree *A);
    void RL(tree *A);
    void LR(tree *A);
    void Add(int num);
    void insertAVL(int k);
    tree *Minimum(tree *node);
    tree *Maximum(tree *node);
    tree *After(tree *node);
    tree *Before(tree *node);
    tree *BeforeImp(tree *node);
    tree *Remove(tree *node);
    tree *RemoveImp(tree *node);
};

void printAVL(string sp, string sn, tree *node)
{
    string cr, cl, cp;
    cr = cl = cp = "  ";
    cr[0] = 218;
    cr[1] = cl[1] = 196;
    cl[0] = 192;
    cp[0] = 179;

    string s;

    if (node)
    {
        s = sp;
        if (sn == cr)
            s[s.length() - 2] = ' ';
        printAVL(s + cp, cr, node->R);

        s = s.substr(0, sp.length() - 2);
        cout << s << sn << node->val << ":" << node->bf << endl;

        s = sp;
        if (sn == cl)
            s[s.length() - 2] = ' ';
        printAVL(s + cp, cl, node->L);
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

tree *Find(tree *node, int search)
{
    if (search == node->val)
        return node;
    else if (search < node->val)
        Find(node->L, search);
    else if (search > node->val)
        Find(node->R, search);
}

//=========================================

void AVLTree::RR(tree *A)
{
    tree *B = A->R;
    tree *p = A->Up;

    A->R = B->L;
    if (A->R != NULL)
        A->R->Up = A;
    B->L = A;
    B->Up = p;
    A->Up = B;
    if (p != NULL)
        if (p->L == A)
            p->L = B;
        else
            p->R = B;
    else
        root = B;

    if (B->bf == -1)
    {
        A->bf = 0;
        B->bf = 0;
    }
    else
    {
        A->bf = -1;
        B->bf = 1;
    }
}

void AVLTree::LL(tree *A)
{
    tree *B = A->L;
    tree *p = A->Up;

    A->L = B->R;
    if (A->L != NULL)
        A->L->Up = A;
    B->R = A;
    B->Up = p;
    A->Up = B;
    if (p != NULL)
        if (p->L == A)
            p->L = B;
        else
            p->R = B;
    else
        root = B;

    if (B->bf == 1)
    {
        A->bf = 0;
        B->bf = 0;
    }
    else
    {
        A->bf = 1;
        B->bf = -1;
    }
}

void AVLTree::RL(tree *A)
{
    tree *B = A->R;
    tree *C = B->L;
    tree *p = A->Up;

    B->L = C->R;
    if (B->L != NULL)
        B->L->Up = B;
    A->R = C->L;
    if (A->R != NULL)
        A->R->Up = A;
    C->L = A;
    C->R = B;
    A->Up = C;
    B->Up = C;
    C->Up = p;
    if (p != NULL)
        if (p->L == A)
            p->L = C;
        else
            p->R = C;
    else
        root = C;

    if (C->bf == -1)
        A->bf = 1;
    else
        B->bf = 0;

    if (C->bf == 1)
        A->bf = -1;
    else
        B->bf = 0;
    C->bf = 0;
}

void AVLTree::LR(tree *A)
{
    tree *B = A->L;
    tree *C = B->R;
    tree *p = A->Up;

    B->R = C->L;
    if (B->R != NULL)
        B->R->Up = B;
    A->L = C->R;
    if (A->L != NULL)
        A->L->Up = A;
    C->R = A;
    C->L = B;
    A->Up = C;
    B->Up = C;
    C->Up = p;
    if (p != NULL)
        if (p->L == A)
            p->L = C;
        else
            p->R = C;
    else
        root = C;

    if (C->bf == 1)
        A->bf = -1;
    else
        B->bf = 0;

    if (C->bf == -1)
        A->bf = 1;
    else
        B->bf = 0;
    C->bf = 0;
}

//=========================================

void AVLTree::Add(int num)
{
    tree *w = new tree();
    w->L = NULL;
    w->R = NULL;
    w->Up = NULL;
    w->val = num;
    w->bf = 0;

    tree *p = root;

    if (p == NULL)
        root = w;
    else
    {
        while (p)
        {
            if (num < p->val)
            {
                if (p->L == NULL)
                {
                    p->L = w;
                    break;
                }
                p = p->L;
            }
            else
            {
                if (p->R == NULL)
                {
                    p->R = w;
                    break;
                }
                p = p->R;
            }
        }
        w->Up = p;

        if (p->bf)
            p->bf = 0;
        if (p->L == w)
            p->bf = 1;
        else
            p->bf = -1;

        tree *r = p->Up;

        while (r != NULL)
        {
            if (r->bf)
            {
                if (r->bf == 1)
                {
                    if (r->R == p)
                        r->bf = 0;
                    else if (p->bf == -1)
                        LR(r);
                    else
                        LL(r);
                }
                else
                {
                    if (r->L == p)
                        r->bf = 0;
                    else if (p->bf == 1)
                        RL(r);
                    else
                        RR(r);
                }
                break;
            };

            if (r->L == p)
                r->bf = 1;
            else
                r->bf = -1;

            p = r;
            r = r->Up;
        }
    }
}

//=========================================

tree *AVLTree::Minimum(tree *node)
{
    if (node != NULL)
    {
        tree *p = node;
        while (p->L)
            p = p->L;
        return p;
    }
}

tree *AVLTree::Maximum(tree *node)
{
    if (node != NULL)
    {
        tree *p = node;
        while (p->R)
            p = p->R;
        return p;
    }
}

//=========================================

tree *AVLTree::After(tree *node)
{
    if (node != NULL)
    {
        if (node->R)
            return Minimum(node->R);
        else
        {
            tree *p = node;
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

tree *AVLTree::Before(tree *node)
{
    if (node != NULL)
    {
        if (node->L)
            return Maximum(node->L);
        else
        {
            tree *p = node;
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

tree *AVLTree::BeforeImp(tree *node) // improved before
{
    tree *p = node;
    if (p != NULL)
    {
        if (p->L)
        {
            p = p->L;
            while (p->R)
                p = p->R;
        }
        else
        {
            tree *r = p;
            while (p && p->R != r)
            {
                r = p;
                p = p->Up;
            }
        }
    }
    return p;
}

//=========================================
tree *AVLTree::Remove(tree *node)
{
    tree *y = new tree();
    bool temp;

    if (node->L != NULL || node->R != NULL)
    {
        cout << Before(node);

        y = Remove(Before(node));
        temp = false;
    }
    else
    {
        if (node->L != NULL)
        {
            y = node->L;
            node->L = NULL;
        }
        else
        {
            y = node->R;
            node->R = NULL;
        }
        node->bf = 0;
        temp = true;
    }

    if (y != NULL)
    {
        y->Up = node->Up;
        y->L = node->L;
        if (y->L != NULL)
            y->L->Up = y;
        y->R = node->R;
        if (y->R != NULL)
            y->R->Up = y;
        y->bf = node->bf;
    }

    if (node->Up != NULL)
    {
        if (node->Up->L == node)
            node->Up->L = y;
        else
            node->Up->R = y;
    }
    else
        root = y;

    tree *z = new tree();

    if (temp == true)
    {
        z = y;
        y = node->Up;
        while (y != NULL)
        {
            if (y->bf == 0)
            {
                if (y->L == z)
                    y->bf = -1;
                else
                    y->bf = 1;
                return node;
            }
            else
            {
                if ((y->bf != 1 || y->L != z) && (y->bf != -1 || y->R != z))
                {
                    tree *t = new tree();
                    if (y->L == z)
                        t = y->R;
                    else
                        t = y->L;
                    if (t->bf != 0)
                    {
                        if (y->bf == 1)
                            LL(y);
                        else
                            RR(y);
                        return node;
                    }
                    else
                    {
                        if (y->bf == t->bf)
                        {
                            if (y->bf == 1)
                                LL(y);
                            else
                                RR(y);
                            z = t;
                            y = t->Up;
                            continue;
                        }
                        break;
                    }
                }
                else
                {
                    y->bf = 0;
                    z = y;
                    y = y->Up;
                    continue;
                }
            }
        }
        if (y->bf == 1)
            LR(y);
        else
            RL(y);
        z = y->Up;
        y = z->Up;
    }
    return node;
}

tree *AVLTree::RemoveImp(tree *node) // improved remove
{
    tree *y = new tree();
    bool temp;

    if (node->L && node->R)
    {
        y = Remove(BeforeImp(node));
        temp = false;
    }
    else
    {
        if (node->L)
        {
            y = node->L;
            node->L = NULL;
        }
        else
        {
            y = node->R;
            node->R = NULL;
        }
        node->bf = 0;
        temp = true;
    }

    if (y)
    {
        y->Up = node->Up;
        y->L = node->L;
        if (y->L)
            y->L->Up = y;
        y->R = node->R;
        if (y->R)
            y->R->Up = y;
        y->bf = node->bf;
    }

    if (node->Up)
    {
        if (node->Up->L == node)
            node->Up->L = y;
        else
            node->Up->R = y;
    }
    else
        root = y;

    tree *z = new tree();

    if (temp)
    {
        z = y;
        y = node->Up;
        while (y)
        {
            if (!y->bf)
            {
                if (y->L == z)
                    y->bf = -1;
                else
                    y->bf = 1;
                break;
            }
            else
            {
                tree *t = new tree();
                if ((y->bf != 1 || y->L != z) && (y->bf != -1 || y->R != z))
                {
                    if (y->L == z)
                        t = y->R;
                    else
                        t = y->L;
                    if (!t->bf)
                    {
                        if (y->bf == 1)
                            LL(y);
                        else
                            RR(y);
                        break;
                    }
                    else if (y->bf == t->bf)
                    {
                        if (y->bf == 1)
                            LL(y);
                        else
                            RR(y);
                        z = t;
                        y = t->Up;
                        continue;
                    }
                    else
                    {
                        if (y->bf == 1)
                            LR(y);
                        else
                            RL(y);
                        z = y->Up;
                        y = z->Up;
                    }
                }
                else
                {
                    y->bf = 0;
                    z = y;
                    y = y->Up;
                }
            }
        }
    }
    return node;
}

//=========================================

int main()
{
    AVLTree drzewo;

    for (int i = 0; i < 32; i++)
        drzewo.Add(i);

    // printBT("", drzewo.root, false);
    printAVL("", "", drzewo.root);
}