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

void DodajZa(node *&x, int val)
{
    node *p = new node;
    p->next = x->next;
    p->val = val;
    x->next = p;
}

void Swap_list(node *&H)
{
    if (H != NULL && H->next != NULL)
    {
        Swap(H);
    }
    else
        return;
    node *temp = H->next;
    while (temp->next && temp->next->next)
    {
        Swap(temp->next);
        temp = temp->next->next;
    }
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

void Split_by_half(node *&H, node *&H1, node *&H2)
{
    if (H != NULL && H->next != NULL)
    {
        node *p = H;
        node *q = H;
        node *e = H;
        while (q->next != NULL)
        {
            p = p->next;
            q = q->next->next;
        }
        H2 = p->next;
        p->next = NULL;
        H1 = e;
    }
}

node *Connect_lists(node *&H, node *&A) // Połączenie dwóch list w jedną (dodanie drugiej na koniec pierwszej)
{
    if (H != NULL)
    {
        node *Con = H;
        node *p = H;
        while (p->next != NULL)
        {
            p = p->next;
        }
        p->next = A;
        return H;
    }
}

int main()
{
    node *H = NULL;
    node *H1 = NULL;
    node *H2 = NULL;
    node *b = new node;

    for (int i = 9; i > 0; i--)
    {
        Add(H, i);
    }
    // Show(H);
    // Swap_list(H);
    Show(H);
    // Split(H, H1, H2);
    Split_by_half(H, H1, H2);
    Show(H1);
    Show(H2);
    H = Connect_lists(H1, H2);
    Show(H);

    return 0;
}