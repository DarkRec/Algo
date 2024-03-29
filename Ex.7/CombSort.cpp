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

void Del(node *&H)
{
    if (H != NULL)
    {
        node *p = H;
        H = p->next; // H = H->next
        delete p;
    }
}

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

void Swap(node *&H)
{
    if (H && H->next)
    {
        node *e = H->next;
        H->next = H->next->next;
        e->next = H->next->next;
        H->next->next = e;
    }
}

void BubbleSort(node *&H)
{
    if (H != NULL && H->next != NULL)
    {
        Add(H, 0);
        node *last = NULL;
        node *p = H;
        while (p->next != last)
        {
            node *p = H;
            while (p->next->next != last)
            {
                if (p->next->val > p->next->next->val)
                {
                    Swap(p);
                }
                p = p->next;
            }
            last = p->next;
        }
    }
    Del(H);
}

void FarSwap(node *p, node *e)
{
    node *b = e->next->next;
    node *a = p->next;
    p->next = e->next;
    e->next = a;
    p->next->next = a->next;
    a->next = b;
}

node *CombSort(node *H, int gap)
{
    if (gap == 0)
        gap = 1;
    if (gap > 1)
    {
        if (gap == 9 || gap == 10)
            gap = 11;

        node *e = H;
        node *b = H;
        for (int n = 0; n < gap; n++)
        {
            e = e->next;
        }
        while (e->next)
        {
            if (b->next->val > e->next->val)
            {
                FarSwap(e, b);
            }
            e = e->next;
            b = b->next;
        }
        CombSort(H, gap / 1.3 - 1);
    }
    else if (gap == 1)
    {
        Del(H);
        BubbleSort(H);
        return H;
    }
}

node *CombSortStart(node *H)
{
    node *p = H;
    int n = 0;
    while (p)
    {
        p = p->next;
        n++;
    }
    Add(H, 0);
    return CombSort(H, n - 1);
}

int main()
{
    node *H = NULL;
    Add(H, 3);
    Add(H, 4);
    Add(H, 8);
    Add(H, 5);
    Add(H, 6);
    Add(H, 2);
    Add(H, 4);
    Add(H, 3);
    Show(H);
    cout << endl;
    H = CombSortStart(H);
    // Show(H);
}


void FarSwap(node *p)
{
    e=p->next->next;
    node *b = e->next->next;
    node *a = p->next;
    p->next = e->next;
    e->next = a;
    p->next->next = a->next;
    a->next = b;
}