#include <iostream>
#include <cstdlib>
#include <fstream>
#include <queue>

using namespace std;

struct node // struct for Array of lists
{
    int to;
    int dist;
    struct node *next;
};

struct edge // struct for edge list
{
    int from;
    int to;
    int dist;
    struct edge *next;
};

//===============================================

node **List;
int Msize, start = 0;
int **MS = new int *[Msize];
int *tab = new int[Msize];

//===============================================

void Add(node *&H, int to, int dist) // add node to end
{
    node *p = new node();
    p->to = to;
    p->dist = dist;
    p->next = NULL;
    if (H == NULL)
        H = p;
    else
    {
        node *temp = H;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = p;
    }
}

void AddEdge(edge *&H, int from, int to, int dist) // add edge to end
{
    edge *e = new edge();
    e->from = from;
    e->to = to;
    e->dist = dist;
    e->next = NULL;
    if (H == NULL)
        H = e;
    else
    {
        edge *temp = H;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = e;
    }
}

void Show(node *H) // show list
{
    cout << "H->";
    node *p = H;
    while (p != NULL)
    {
        cout << "(" << p->to << "/" << p->dist << ")"
             << "->";
        p = p->next;
    }
    cout << "NULL" << endl;
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

void ShowListGraph(node **List, int size) // print array of lists
{
    cout << endl;
    for (int i = 0; i < size; i++)
    {
        cout << "(H" << i << ")->";
        node *p = List[i];
        while (p != NULL)
        {
            cout << "(" << p->to << "/" << p->dist << ")->";
            p = p->next;
        }
        cout << "NULL" << endl;
    }
}

node **MatrixToList(int **Matrix, int size) // convert matrix to array of lists
{
    node **LS = new node *[size];
    for (int i = 0; i < size; i++)
        LS[i] = NULL;

    int dist;
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
        {
            dist = Matrix[i][j];
            if (dist != 0)
                Add(LS[i], j, dist);
        }
    return LS;
}

//===============================================

struct path
{
    int dist;
    int prev;
};

void Bellman_Ford(edge *EdgeList, int size, int start)
{
    path *tab = new path[size];
    for (int i = 0; i < size; i++)
    {
        tab[i].dist = 1000;
        tab[i].prev = -1;
    }
    tab[start].dist = 0;
}

//===============================================

void DFS(int start) // DFS - depth first search - szukanie w głąb
{
    if (tab[start] == 0)
    {
        tab[start] = 1;
        node *p = List[start];
        while (p)
        {
            if (tab[p->to == 0])
                DFS(p->to);
            else
                break;
            p = p->next;
        }
    }
}

void odwiedz(int n)
{
    // wykonaj jakies czynnosci
    // w przypadku odwiedzenia wierzcholka o numerze n
    cout << "Odwiedzono wierzchołek o numerze: " << n << endl;
}

void BFS(int start) // BFS - breadth first search - szukanie wszerz
{
}
//===============================================

int main()
{
    fstream matrix; // Macierz z pliku
    matrix.open("graf.txt");

    matrix >> Msize;
    cout << Msize << endl
         << endl;

    for (int i = 0; i < Msize; i++)
    {
        MS[i] = new int[5];

        for (int j = 0; j < Msize; j++)
            matrix >> MS[i][j];
    }
    cout << endl;
    matrix.close();

    ShowMatrixGraph(MS, Msize);
    List = MatrixToList(MS, Msize);
    // ShowListGraph(List, Msize);

    for (int i = 0; i < Msize; i++)
        tab[i] = 0;

    // DFS(0);
    BFS(0);

    for (int i = 0; i < Msize; i++)
        cout << tab[i];
    // Bellman_Ford(List, Msize, start);
}
