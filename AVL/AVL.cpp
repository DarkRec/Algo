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

void printAVL(string sp, string sn, tree *root)
{
    string cr, cl, cp;
    cr = cl = cp = "  ";
    cr[0] = 218;
    cr[1] = cl[1] = 196;
    cl[0] = 192;
    cp[0] = 179;

    string s;

    if (root)
    {
        s = sp;
        if (sn == cr)
            s[s.length() - 2] = ' ';
        printAVL(s + cp, cr, root->R);

        s = s.substr(0, sp.length() - 2);
        cout << s << sn << root->val << ":" << root->bf << endl;

        s = sp;
        if (sn == cl)
            s[s.length() - 2] = ' ';
        printAVL(s + cp, cl, root->L);
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

//=========================================

tree *Find(tree *&root, int val)
{
    if (val == root->val)
        return root;
    else if (val < root->val)
        Find(root->L, val);
    else if (val > root->val)
        Find(root->R, val);
}

//=========================================

void RR(tree *&root, tree *A)
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

void LL(tree *&root, tree *A)
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

void RL(tree *&root, tree *A)
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

void LR(tree *&root, tree *A)
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

void Add(tree *&root, int val)
{
    tree *w = new tree();
    w->L = NULL;
    w->R = NULL;
    w->Up = NULL;
    w->val = val;
    w->bf = 0;
    tree *p = root;

    if (p == NULL)
        root = w;
    else
    {
        while (p)
        {
            if (val < p->val)
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
                        LR(root, r);
                    else
                        LL(root, r);
                }
                else
                {
                    if (r->L == p)
                        r->bf = 0;
                    else if (p->bf == 1)
                        RL(root, r);
                    else
                        RR(root, r);
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

//=========================================

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

tree *BeforeImp(tree *node) // improved before
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
tree *Remove(tree *&root, tree *x)
{
    tree *y = new tree();
    bool temp;

    if (x->L != NULL || x->R != NULL)
    {
        y = Remove(root, Before(x));
        temp = false;
    }
    else
    {
        if (x->L != NULL)
        {
            y = x->L;
            x->L = NULL;
        }
        else
        {
            y = x->R;
            x->R = NULL;
        }
        x->bf = 0;
        temp = true;
    }

    if (y != NULL)
    {
        y->Up = x->Up;
        y->L = x->L;
        if (y->L != NULL)
            y->L->Up = y;
        y->R = x->R;
        if (y->R != NULL)
            y->R->Up = y;
        y->bf = x->bf;
    }

    if (x->Up != NULL)
    {
        if (x->Up->L == x)
            x->Up->L = y;
        else
            x->Up->R = y;
    }
    else
        root = y;

    tree *z = new tree();

    if (temp == true)
    {
        z = y;
        y = x->Up;
        while (y != NULL)
        {
            if (y->bf == 0)
            {
                if (y->L == z)
                    y->bf = -1;
                else
                    y->bf = 1;
                return x;
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
                            LL(root, y);
                        else
                            RR(root, y);
                        return x;
                    }
                    else
                    {
                        if (y->bf == t->bf)
                        {
                            if (y->bf == 1)
                                LL(root, y);
                            else
                                RR(root, y);
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
            LR(root, y);
        else
            RL(root, y);
        z = y->Up;
        y = z->Up;
    }
    return x;
}

tree *RemoveImp(tree *&root, tree *x) // improved remove
{
    tree *y = new tree();
    bool temp;

    if (x->L && x->R)
    {
        y = Remove(root, BeforeImp(x));
        temp = false;
    }
    else
    {
        if (x->L)
        {
            y = x->L;
            x->L = NULL;
        }
        else
        {
            y = x->R;
            x->R = NULL;
        }
        x->bf = 0;
        temp = true;
    }

    if (y)
    {
        y->Up = x->Up;
        y->L = x->L;
        if (y->L)
            y->L->Up = y;
        y->R = x->R;
        if (y->R)
            y->R->Up = y;
        y->bf = x->bf;
    }

    if (x->Up)
    {
        if (x->Up->L == x)
            x->Up->L = y;
        else
            x->Up->R = y;
    }
    else
        root = y;

    tree *z = new tree();

    if (temp)
    {
        z = y;
        y = x->Up;
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
                            LL(root, y);
                        else
                            RR(root, y);
                        break;
                    }
                    else if (y->bf == t->bf)
                    {
                        if (y->bf == 1)
                            LL(root, y);
                        else
                            RR(root, y);
                        z = t;
                        y = t->Up;
                        continue;
                    }
                    else
                    {
                        if (y->bf == 1)
                            LR(root, y);
                        else
                            RL(root, y);
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
    return x;
}

//=========================================

int main()
{
    int Tk[32]; // tablica kluczy węzłów
    tree *root = NULL;

    for (int i = 0; i < 32; i++)
    {
        Tk[i] = i + 1;
        Add(root, Tk[i]);
    }

    printAVL("", "", root);
    RemoveImp(root, Find(root, 8));
    RemoveImp(root, Find(root, 28));
    Add(root, 18);
    printAVL("", "", root);
}
