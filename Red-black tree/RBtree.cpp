#include <iostream>

using namespace std;

struct tree
{
    int val;
    int color; // 1 - red , 0 - black
    tree *Up;
    tree *R;
    tree *L;
};

class RBTree
{
public:
    tree S;
    tree *root;
    RBTree()
    {
        S.color = 0;
        S.Up = &S;
        S.R = &S;
        S.L = &S;
        root = &S;
    }
    void printRB(string sp, string sn, tree *node);

    void RR(tree *A);
    void LL(tree *A);
    void Add(int num);
    void Remove(tree *node);
    tree *Minimum(tree *p);
    tree *After(tree *p);
};

void RBTree::printRB(string sp, string sn, tree *node)
{
    string cr, cl, cp;
    cr = cl = cp = "  ";
    cr[0] = 218;
    cr[1] = cl[1] = 196;
    cl[0] = 192;
    cp[0] = 179;

    string s;

    if (node != &S)
    {
        s = sp;
        if (sn == cr)
            s[s.length() - 2] = ' ';
        printRB(s + cp, cr, node->R);

        s = s.substr(0, sp.length() - 2);
        if (node->color == 0)
            cout << s << sn << node->val << ":"
                 << "B" << endl;
        else
            cout << s << sn << node->val << ":"
                 << "R" << endl;

        s = sp;
        if (sn == cl)
            s[s.length() - 2] = ' ';
        printRB(s + cp, cl, node->L);
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
//========================================

void RBTree::LL(tree *A)
{
    tree *B = A->R;
    if (B != &S)
    {
        tree *p = A->Up;
        A->R = B->L;
        if (A->R != &S)
            A->R->Up = A;
        B->L = A;
        B->Up = p;
        A->Up = B;
        if (p != &S)
        {
            if (p->L == A)
                p->L = B;
            else
                p->R = B;
        }
        else
            root = B;
    }
}

void RBTree::RR(tree *A)
{
    tree *B = A->L;
    if (B != &S)
    {
        tree *p = A->Up;
        A->L = B->R;
        if (A->L != &S)
            A->L->Up = A;
        B->R = A;
        B->Up = p;
        A->Up = B;
        if (p != &S)
        {
            if (p->L == A)
                p->L = B;
            else
                p->R = B;
        }
        else
            root = B;
    }
}

//====================

void RBTree::Add(int num)
{
    tree *p = new tree();
    p->L = &S;
    p->R = &S;
    p->Up = root;
    p->val = num;
    if (p->Up != &S)
        while (true)
        {
            if (num < p->Up->val) // 10
            {
                if (p->Up->L == &S)
                {
                    p->Up->L = p;
                    break;
                }
                p->Up = p->Up->L;
                continue;
            }
            else
            {
                if (p->Up->R == &S)
                {
                    p->Up->R = p;
                    break;
                }
                p->Up = p->Up->R;
                continue;
            }
        }
    else
        root = p;
    p->color = 1; // 17

    tree *q = new tree();
    while (p != root && p->Up->color == 1)
    {
        if (p->Up == p->Up->Up->L)
        {
            q = p->Up->Up->R;
            if (q->color == 0)
            {
                if (p == p->Up->R)
                {
                    p = p->Up;
                    LL(p);
                }
                p->Up->color = 0;
                p->Up->Up->color = 1;
                RR(p->Up->Up);
                break;
            }
            p->Up->color = 0;
            q->color = 0;
            p->Up->Up->color = 1;
            p = p->Up->Up;
            continue;
        }
        else
        {
            q = p->Up->Up->L;
            if (q->color != 0)
            {
                p->Up->color = 0;
                q->color = 0;
                p->Up->Up->color = 1;
                p = p->Up->Up;
                continue;
            }
            else
            {
                if (p == p->Up->L)
                {
                    p = p->Up;
                    RR(p);
                }
                p->Up->color = 0;
                p->Up->Up->color = 1;
                LL(p->Up->Up);
                break;
            }
        }
    }
    root->color = 0;
}

//========================================

tree *RBTree::Minimum(tree *node)
{
    if (node != &S)
    {
        tree *p = node;
        while (p->L != &S)
            p = p->L;
        return p;
    }
}

tree *RBTree::After(tree *node)
{
    if (node != &S)
    {
        if (node->R != &S)
            return Minimum(node->R);
        else
        {
            tree *p = node->Up;
            while (p != &S && node == p->R)
            {
                node = p;
                p = p->Up;
            }
            return p;
        }
    }
    else
        return &S;
}

//====================

void RBTree::Remove(tree *node)
{
    tree *p = node;
    tree *q;
    if (p->L == &S || p->R == &S)
        q = p;
    else
        q = After(p);

    tree *e;
    if (q->L != &S)
        e = q->L;
    else
        e = q->L;
    e->Up = q->Up;
    if (q->Up == &S)
    {
        root = e;
    }
    else
    {
        if (q == q->Up->L)
            q->Up->L = e;
        else
            q->Up->R = e;
    }
    if (q != p)
        p->val = q->val;
    if (q->color == 0)
    {
        tree *r;
        while (e != root && e->color == 0)
        {
            if (e != e->Up->R)
            {
                r = e->Up->R;
                if (r->color == 1)
                {
                    r->color = 0;
                    e->Up->color = 1;
                    LL(e->Up);
                    r = e->Up->R;
                }
                if (r->L->color == 1 || r->R->color == 1)
                {
                    if (r->R->color == 0)
                    {
                        r->L->color = 0;
                        r->color = 1;
                        RR(r);
                        r = e->Up->R;
                    }
                    r->color = e->Up->color;
                    e->Up->color = 0;
                    r->R->color = 0;
                    LL(e->Up);
                    e = root;
                    continue;
                }
                else
                {
                    r->color = 1;
                    e = e->Up;
                    continue;
                }
            }
            else
            {
                if (r->color == 1)
                {
                    r->color = 0;
                    e->Up->color = 1;
                    RR(e->Up);
                    r = e->Up->L;
                }
                if (r->L->color == 1 || r->R->color == 1)
                    break;
                r->color = 1;
                e = e->Up;
                continue;
            }
        }
    }
    e->color = 0;
    delete q;
}

int main()
{
    RBTree drzewoRB;

    for (int i = 0; i < 16; i++)
    {
        drzewoRB.Add(i + 1);
    }
    drzewoRB.printRB("", "", drzewoRB.root);

    // drzewoRB.Remove(drzewoRB.root->R);
}
