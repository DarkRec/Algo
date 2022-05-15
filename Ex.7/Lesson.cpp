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

void Show(node *H)
{
    cout << "H->";
    node *p = H;
    while (p != NULL)
    {

        cout << "(" << p->val << ")->";
        p = p->next;
    }
    cout << "NULL" << endl;
}

void Split(node *&H, node *&H1, node *&H2)
{
    if (H != NULL && H->next != NULL)
    {
        node *p = H;
        node *e = H;
        int count = 0;
        while (p->next != NULL)
        {
            count++;
            p = p->next;
        }
        H1 = e;
        for (int i = 0; i < count / 2; i++)
        {
            e = e->next;
        }
        H2 = e->next;
        e->next = NULL;
    }
}

void AddAndShift(node *&tail, node *&src)
{
    tail->next = src;
    tail = tail->next;
    src = src->next;
}

node *Merge(node *H, node *&H1, node *&H2) // Połączenie dwóch list w jedną (dodanie drugiej na koniec pierwszej)
{
    node *tmp1 = H1;
    node *tmp2 = H2;

    if (tmp1->val <= tmp2->val)
    {
        H = tmp1;
        tmp1 = tmp1->next;
    }
    else
    {
        H = tmp2;
        tmp2 = tmp2->next;
    }
    node *tail = H;
    while (tmp1 && tmp2)
    {
        if (tmp1->val <= tmp2->val)
            AddAndShift(tail, tmp1);
        else
            AddAndShift(tail, tmp2);
    }
    if (tmp1)
        tail->next = tmp1;
    else
        tail->next = tmp2;
    H1 = NULL;
    H2 = NULL;
    return tail;
}

void MS(node *H)
{
    if (H->next)
    {
        node *H1 = NULL;
        node *H2 = NULL;
        Split(H, H1, H2);
        H = NULL;
        MS(H1);
        MS(H2);
        H = Merge(H, H1, H2);
    }
}

int main()
{
    node *H = NULL;
    Add(H, 7);
    Add(H, 4);
    Add(H, 12);
    Add(H, -6);
    Add(H, 2);
    Add(H, -8);
    Add(H, -3);
    Add(H, -9);
    Show(H);
    MS(H);
    Show(H);
}