#include <iostream>

using namespace std;

struct node
{
    int val;
    node *next;
};

void Add(node *&H, int val)
{
    node *p = new node;
    p->next = H;
    p->val = val;
    H = p;
}

void Show(node *H)
{
    cout << "H->";
    node *p = H;
    while (p != NULL)
    {
        cout << p->val << "->";
        p = p->next;
    }
    cout << "NULL" << endl;
}

void AddToEnd(node *&H, int x)
{
    node *p = H;
    while (p->next != NULL)
    {
        p = p->next;
    }
    node *e = new node;
    e->val = x;
    e->next = NULL;
    p->next = e;
}

void Delete(node *&H)
{
    if (H != NULL)
    {
        node *p = H;
        H = p->next;
        delete p;
    }
}

void DodajZa(node *&x, int val)
{
    node *p = new node;
    p->next = x->next;
    p->val = val;
    x->next = p;
}

void WstawXzaY(node *&x, node *&y)
{
    node *p = new node;
    p->val = x->val;
    p->next = y->next;
    y->next = p;

    node *d = x;
    x = d->next;
    delete d;
}

void XDKopia(node *H)
{
    cout << "H->";
    node *p = H;
    while (p != NULL)
    {
        cout << p->val << "->";
        cout << p->val << "->";
        p = p->next;
    }
    cout << "NULL" << endl;
}

void Kopia(node *H)
{
    node *p = H;
    while (p != NULL)
    {
        node *e = new node;
        e->val = p->val;
        e->next = p->next;
        p->next = e;
        p = e->next;
    }
}

void ValKopia(node *H)
{
    node *p = H;
    while (p != NULL)
    {
        for (int i = 0; i < p->val - 1; i++)
        {
            DodajZa(p, p->val);
            p = p->next;
        }
        p = p->next;
    }
}

int main()
{
    node *Head = NULL;
    Add(Head, 4);
    Add(Head, 2);
    // Add(Head->next->next, 7);
    Show(Head);
    AddToEnd(Head, 5);
    // Kopia(Head);
    ValKopia(Head);
    // WstawXzaY(Head, Head->next->next);
    Show(Head);
}