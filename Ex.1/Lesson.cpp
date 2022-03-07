#include <iostream>

using namespace std;

struct node
{
    int val;
    node *next;
};

void Add(node *&H, int x)
{
    node *p = new node;
    p->next = H;
    p->val = x;
    H = p;
};

void show(node *H)
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

void del(node *&H)
{
    if (H != NULL)
    {
        node *p = H;
        H = p->next; // H = H->next
        delete p;
    }
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

    // alternatywa: Add(p->next, x);
}

int main()
{

    node *H = NULL;
    node *b = new node;
    cout << H << endl;
    Add(H, 5);
    cout << H << endl;

    show(H);
    Add(H, 10);
    show(H);

    del(H->next);
    show(H);
    Add(H, 5);
    show(H);
    AddToEnd(H, 2);
    show(H);

    system("pause");
    return 0;
}