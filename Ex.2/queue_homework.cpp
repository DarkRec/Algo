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
    cout << "(Tail)" << endl;
}

node *Front(node *&H)
{
    if (H != NULL)
    {
        cout << "Front: " << H->next << endl;
        return H->next;
    }
}

node *Tail(node *&H)
{
    if (H != NULL)
    {
        node *p = H;
        while (p->next)
        {
            p = p->next;
        }
        cout << "Tail: " << p->next << endl;
        return p->next;
    }
}

void Pop(node *&H)
{
    if (H != NULL)
    {
        node *p = H;
        H = p->next; // H = H->next
        delete p;
    }
}

void Push(node *&H, int x)
{
    node *t = new node;
    t->next = H;
    H = t;

    node *p = H;
    while (p->next)
        p = p->next;
    node *e = new node;
    e->next = p->next;
    e->val = x;
    p->next = e;
    Pop(H);
};

bool Empty(node *&H)
{
    if (H == NULL)
        cout << "Queue is Empty" << endl;
    else
        cout << "Queue is not Empty" << endl;
    return H == NULL;
}

int main()
{
    node *F = NULL;

    Push(F, 1);
    Push(F, 2);
    Push(F, 3);
    Push(F, 4);
    Show(F);
    Pop(F);
    Push(F, 1);
    Show(F);
    Empty(F);
    Front(F);
    Pop(F);
    Tail(F);
    Pop(F);
    Pop(F);
    Pop(F);
    Empty(F);
}