#include <iostream>
#include <cstdlib>
#include <fstream>

using namespace std;

struct node
{
    int nr;
    int val;
    struct node *next;
};

void Add(node *&H, int x, int y)
{
    node *p = new node;
    p->next = H;
    p->nr = x;
    p->val = y;
    H = p;
};

void Show(node *H)
{
    node *p = H;
    while (p != NULL)
    {
        cout << "(" << p->nr << "/" << p->val << ")->";
        p = p->next;
    }
    cout << "NULL" << endl;
}

int main()
{
    fstream plik;

    plik.open("graf.txt");

    int size;

    plik >> size;
    cout << size << endl;

    /*
    int **MS = new int *[size];

    for (int i = 0; i < size; i++)
    {
        MS[i] = new int[5];

        for (int j = 0; j < size; j++)
            plik >> MS[i][j];
    }

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
            cout << MS[i][j] << " ";
        cout << endl;
    }*/

    node **LS = new node *[size];
    for (int i = 0; i < size; i++)
        LS[i] = NULL;

    int val;
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
        {
            plik >> val;
            if (val != 0)
                Add(LS[i], j, val);
        }

    for (int i = 0; i < size; i++)
    {
        cout << "(H" << i << ")->";
        Show(LS[i]);
    }
    plik.close();
}
// Dostaje macierz sąsiedztwa / liste sąsiedztwa
// Macierz -> Lista
// Lista -> Macierz
// Lista Krawędzi
// Sposób czytania listy krawędzi
// Generacja z listy krawędzi Listy sąsiedztwa
// Generacja z Listy krawędzi Macierz sąsiedztwa