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

        cout << p->val << "->";
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

void CombSort(node *H, int gap)
{
    while (gap > 1)
    {
        if (gap == 9 || gap == 10)
            gap = 11;
        else if (gap == 0)
            gap = 1;

        if (gap == 1)
            BubbleSort(H);
        else
        {
            gap = gap / 1.3;
            CombSort(H, gap);
        }
    }
}

int main()
{
    node *H = NULL;
    Add(H, 3);
    Add(H, 15);
    Add(H, 22);
    Add(H, -6);
    Add(H, 3);
    Add(H, 4);
    Add(H, 8);
    Show(H);

    node *p = H;
    int n = 0;
    while (p)
    {
        p = p->next;
        n++;
    }
    CombSort(H, n);
}