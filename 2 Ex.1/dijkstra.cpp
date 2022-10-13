#include <iostream>
#include <cstdlib>
#include <fstream>

using namespace std;

const int INT_MAX = 2147483647;

// Typy danych
struct dane
{
    int dystans;
    int poprzednik;
    bool odwiedzony;
};

int Minimum(int n, dane *tab)
{
    int min = -1;
    int mindist = INT_MAX;
    for (int i = 0; i < n; i++)
    {
        if (!tab[i].odwiedzony && tab[i].dystans < mindist)
        {
            min = i;
            mindist = tab[i].dystans;
        }
    }
    return min;
}

dane *Dijkstra(int **macierz, int n, int start)
{
    dane *tab = new dane[n];
    for (int i = 0; i < n; i++)
    {
        tab[i].dystans = (i == start) ? 0 : INT_MAX;
        tab[i].odwiedzony = false;
        tab[i].poprzednik = -1;
    }
    int u = Minimum(n, tab);
    while (u != -1)
    {
        tab[u].odwiedzony = true;
        for (int i = 0; i < n; i++)
        {
            if (macierz[u][i] > 0 && tab[u].dystans + macierz[u][i] < tab[i].dystans)
            {
                tab[i].dystans = tab[u].dystans + macierz[u][i];
                tab[i].poprzednik = u;
            }
        }
        u = Minimum(n, tab);
    }
    return tab;
}

void wypiszdane(int i, dane d)
{
    cout << i << "\t";
    if (!d.odwiedzony)
    {
        cout << "nieodwiedzony";
    }
    else
    {
        if (d.poprzednik == -1)
            cout << "brak";
        else
            cout << d.poprzednik;
        cout << "\t" << d.dystans;
    }
    cout << endl;
}

void ShowMatrixGraph(int **MS, int size) // print matrix
{
    cout << endl;
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
            cout << MS[i][j] << " ";
        cout << endl;
    }
}

int main()
{

    fstream matrix; // Macierz z pliku
    matrix.open("graf2.txt");

    int Msize;
    matrix >> Msize;
    cout << Msize << endl
         << endl;

    int **MS = new int *[Msize];

    for (int i = 0; i < Msize; i++)
    {
        MS[i] = new int[5];

        for (int j = 0; j < Msize; j++)
            matrix >> MS[i][j];
    }
    ShowMatrixGraph(MS, Msize);

    cout << endl;
    matrix.close();

    cout << "Podaj wierzcholek poczatkowy ";
    int start;
    cin >> start;

    dane *tab = Dijkstra(MS, Msize, start);
    cout << "Wezel\tPoprz.\tDystans" << endl;
    for (int i = 0; i < Msize; i++)
        wypiszdane(i, tab[i]);
    return 0;
}
