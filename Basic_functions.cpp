#include <iostream>
#include <time.h>

using namespace std;

struct node // Tworzenie struktury node (węzła)
{
    int val;
    node *next;
};

void Add(node *&H, int x) // Dodanie węzła do listy (na początek, przed Head'a)
{
    node *p = new node;
    p->next = H;
    p->val = x;
    H = p;
};

void Show(node *H) // Wypisanie całej listy, od Head'a do NULL'a
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

void Delete(node *&H) // Usunięcie węzła z listy, oraz z pamięci
{
    if (H != NULL)
    {
        node *p = H;
        H = p->next;
        delete p;
    }
}

void Swap(node *&H) // Zamiana dwóch sąsiadujących ze sobą węzłów
{
    if (H && H->next)
    {
        node *p = H;
        H = H->next;
        p->next = p->next->next;
        H->next = p;
    }
}

node *Reverse(node *&H) // Odwórcenie listy
{
    if (H != NULL)
    {
        node *p = H;
        node *e = NULL;
        node *R = NULL;
        while (p != NULL)
        {
            e = p->next;
            p->next = R;
            R = p;
            p = e;
        }
        return R;
    }
}

node *Reverse_clone(node *&H) // Stworzenie osobnej, odwróconej listy
{
    if (H != NULL)
    {
        node *R = NULL;
        node *p = H;
        while (p != NULL)
        {
            Add(R, p->val);
            p = p->next;
        }
        return R;
    }
}

node *Clone(node *&H) // Skopiowanie listy (z użyciem odwóconej kopii i odwracania)
{
    node *A = Reverse_clone(H);
    A = Reverse(A);
    return A;
}

node *Connect_lists(node *&H, node *&A) // Połączenie dwóch list w jedną (dodanie drugiej na koniec pierwszej)
{
    if (H != NULL)
    {
        node *Hc = Clone(H);
        node *Ac = Clone(A);
        node *Con = Hc;
        node *p = Hc;
        while (p->next != NULL)
        {
            p = p->next;
        }
        p->next = Ac;
        return Hc;
    }
}

void Split_by_half(node *&H, node *&H1, node *&H2) // Podzielenie listy na pół na dwie listy
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

int main()
{
    srand(time(NULL));
    node *H = NULL; // Tworzenie pustej listy

    for (int i = 0; i < 5; i++)
    {
        Add(H, (rand() % 20 + 1));
    }
    Show(H);
    node *c = Clone(H);
    // Show(c);
    Swap(c->next);
    node *rc = Reverse_clone(H);
    // Show(rc);
    Delete(rc);
    node *Con = Connect_lists(H, rc);
    Show(Con);
    node *A = NULL;
    node *B = NULL;
    Split_by_half(Con, A, B);
    Show(A);
    Show(B);
}