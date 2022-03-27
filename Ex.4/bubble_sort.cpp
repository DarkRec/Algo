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

int main()
{
    node *H = NULL;
    Add(H, 1);
    Add(H, 3);
    Add(H, 2);
    Add(H, 5);
    Add(H, 7);
    Add(H, 10);

    Show(H);
    BubbleSort(H);
    Show(H);
    // system("pause");
    return 0;
}