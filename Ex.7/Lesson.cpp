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
        cout << p->val << "->";
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

node *Merge(node *&H1, node *&H2)
{
    node *H;
    if (H1 == NULL)
        return H2;
    else if (H2 == NULL)
        return H1;

    if (H1->val < H2->val)
    {
        H = H1;
        H->next = Merge(H1->next, H2);
    }
    else
    {
        H = H2;
        H->next = Merge(H1, H2->next);
    }

    return H;
}

void MS(node *&H)
{
    if (H->next)
    {
        node *H1 = NULL;
        node *H2 = NULL;
        Split(H, H1, H2);
        MS(H1);
        MS(H2);
        H = Merge(H1, H2);
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
    Show(H);
    MS(H);
    Show(H);
}