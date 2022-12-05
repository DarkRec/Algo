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

void printAVL(string sp, string sn, tree *v)
{
    string cr, cl, cp;
    cr = cl = cp = "  ";
    cr[0] = 218;
    cr[1] = cl[1] = 196;
    cl[0] = 192;
    cp[0] = 179;

    string s;

    if (v)
    {
        s = sp;
        if (sn == cr)
            s[s.length() - 2] = ' ';
        printAVL(s + cp, cr, v->R);

        s = s.substr(0, sp.length() - 2);
        cout << s << sn << v->val << ":" << v->bf << endl;

        s = sp;
        if (sn == cl)
            s[s.length() - 2] = ' ';
        printAVL(s + cp, cl, v->L);
    }
}

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

int main()
{
    int Tk[32]; // tablica kluczy węzłów
    tree *root = NULL;

    for (int i = 0; i < 32; i++)
    {
        Tk[i] = i + 1;
        Add(root, Tk[i]);
    }

    printBT("", root, false);
    printAVL("", "", root);
    // cout << root->val;
}
