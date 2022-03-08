#include <iostream>

using namespace std;

struct node
{
    int val;
    node *next;
};

void Show(node *H)
{
    cout << "(Head)->";
    node *p = H;
    while (p != NULL)
    {
        cout << p->val << "->";
        p = p->next;
    }
    cout << "NULL" << endl;
}

void Add(node *&H, int val)
{
    node *t = new node;
    t->next = H;
    H = t;

    node *p = H;
    while (p->next && p->next->val < val)
        p = p->next;

    node *e = new node;
    e->next = p->next;
    e->val = val;
    p->next = e;

    node *d = t;
    H = d->next;
    delete d;
}

void Zamiana1zLast(node *&H)
{
    if (H != NULL && H->next != NULL)
    {
        node *p = H;
        while (p->next->next)
            p = p->next;

        node *e = new node;
        e->val = H->val;
        e->next = p->next;
        p->next = e;

        p = p->next;
        p->next->next = H->next;
        H = p->next;
        p->next = NULL;
    }
}

int main()
{
    node *H = NULL;

    Add(H, 10);
    Add(H, 20);
    Add(H, 15);
    Add(H, 25);
    Add(H, -30);
    Add(H, 5);
    Add(H, -12);
    Show(H);
    Zamiana1zLast(H);
    Show(H);
}