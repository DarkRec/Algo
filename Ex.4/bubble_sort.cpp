#include <iostream>
#include <time.h>
#define size 100000

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
    for (int i = 0; i < size; i++)
    {
        Add(H, rand() % 100);
    }

    // Show(H);

    clock_t start = clock();
    BubbleSort(H);
    clock_t end = clock();

    double elapsed = double(end - start) / CLOCKS_PER_SEC;
    cout << "Time measured: " << elapsed << "seconds.\n";
    // Show(H);
    //  system("pause");
    return 0;
}