#include <iostream>

using namespace std;

struct node
{
    int val;
    node *next;
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

void Add(node *&H, int x)
{
    node *p = new node;
    p->next = H;
    p->val = x;
    H = p;
};

void Dodaj_przed(node *&H, int x, int y) // Dodawanie x przed y
{
    if (H != NULL)
    {
        node *p = H;
        while (p->next != NULL && p->next->val != y)
        {
            p = p->next;
        }
        if (p->next != NULL)
        {
            node *e = new node; // Add(p->next,x)
            e->val = x;
            e->next = p->next;
            p->next = e;
        }
    }
}

void Swap(node *&H) // Zamiana sąsiadujących elementów
{
    if (H && H->next)
    {
        node *p = H;
        H = H->next; // H=p->next
        p->next = p->next->next;
        H->next = p;
    }
}

void Swap_x(node *&H, int x) // zamiana el. x ze swoim następnikiem
{
    if (H != NULL && H->next != NULL)
    {
        if (H->val == x)
            Swap(H);
        else
        {
            node *p = H;
            while (p->next != NULL && p->next->val != x)
            {
                p = p->next;
            }
            if (p->next)
                Swap(p->next);
        }
    }
}

int main()
{
    node *H = NULL;
    node *b = new node;
    Add(H, 6);
    Add(H, 8);
    Add(H, 1);
    Show(H);

    Dodaj_przed(H, 10, 8);
    Show(H);

    Swap(H);
    Show(H);

    Swap_x(H, 8);
    Show(H);
}