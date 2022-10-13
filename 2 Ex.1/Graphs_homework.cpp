#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>

using namespace std;

const int INT_MAX = 2147483647;

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

void Add(edge *&H, int from, int to) // add node to end
{
    cout << endl
         << "p" << endl;
    edge *p = new edge;
    p->next = H;
    p->from = from;
    p->to = to;
    H = p;
}

//===============================================

void AddEdge(edge *&H, int from, int to) // add edge to end
{
    edge *e = new edge;
    e->from = from;
    e->to = to;
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

//===============================================

void ShowEdgeList(edge *EdgeList) // print edge list
{
    cout << endl;
    edge *p = EdgeList;
    while (p)
    {
        cout << endl
             << "( " << p->from << " / " << p->to << " )";
        p = p->next;
    }
}

//===============================================

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

//===============================================

void EdgeLength(edge *EdgeList)
{
    edge *p = EdgeList;
    int len = 0;
    while (p->next)
    {
        len++;
        p = p->next;
    }
    cout << endl
         << len << endl;
}

//===============================================

void NoDuplicates(edge *&H) // remove duplicates ( [1/2] - [1/2])
{
    edge *p, *q, *dup;
    p = H;
    while (p != NULL && p->next != NULL)
    {
        q = p;
        while (q->next != NULL)
        {
            if (p->from == q->next->from && p->to == q->next->to)
            {
                dup = q->next;
                q->next = q->next->next;
                delete (dup);
            }
            else
                q = q->next;
        }
        p = p->next;
    }
}

//===============================================

int **EdgeListToMatrix(edge *EdgeList, int size) // convert edgelist to matrix
{
    int **MS = new int *[size];

    edge *p = EdgeList;
    for (int i = 0; i < size; i++)
    {
        MS[i] = new int[5];
        for (int j = 0; j < size; j++)
        {
            if (p->from == i && p->to == j)
            {
                MS[i][j] = 1;
                if (p->next)
                    p = p->next;
            }
            else
                MS[i][j] = 0;
        }
    }
    return MS;
}

//===============================================
// Dijkstra

struct dane
{
    int dist;
    int prev;
    bool visited;
};

int Minimum(int n, dane *tab)
{
    int min = -1;
    int mindist = INT_MAX;
    for (int i = 0; i < n; i++)
    {
        if (!tab[i].visited && tab[i].dist < mindist)
        {
            min = i;
            mindist = tab[i].dist;
        }
    }
    return min;
}

dane Dijkstra(int **macierz, int n, int start, int end)
{
    dane *tab = new dane[n];
    for (int i = 0; i < n; i++)
    {
        tab[i].dist = (i == start) ? 0 : INT_MAX;
        tab[i].visited = false;
        tab[i].prev = -1;
    }
    int m = Minimum(n, tab);
    while (m != -1)
    {
        tab[m].visited = true;
        for (int i = 0; i < n; i++)
        {
            if (macierz[m][i] > 0 && tab[m].dist + macierz[m][i] < tab[i].dist)
            {
                tab[i].dist = tab[m].dist + macierz[m][i];
                tab[i].prev = m;
            }
        }
        m = Minimum(n, tab);
    }
    return tab[end];
}

//===============================================

void connection(int **macierz, int size)
{
    cout << endl
         << "Podaj wierzcholek poczatkowy: ";
    int start, end;
    cin >> start;
    cout << "Podaj wierzcholek koncowy: ";
    cin >> end;
    cout << endl;
    dane con = Dijkstra(macierz, size, start, end);

    if (!con.visited)
    {
        cout << "niepolaczone";
    }
    else
    {
        if (con.prev == -1)
            cout << "ten sam wezel";
        else
            cout << "polaczone";
    }
}

//===============================================

int main()
{
    int Nodes, Edges;
    edge *EdgeList = NULL;
    int x, y;

    cout << endl
         << "1. Wczytanie z  pliku | 2. Wczytanie z klawaitury" << endl;

    int read;
    cin >> read;
    switch (read)
    {
    case 1:
    {
        cout << endl
             << "Wpisz nazwe pliku txt" << endl;
        string fileName;
        cin >> fileName;
        fstream list; // lista z pliku

        int found = fileName.find('.');
        if (found > fileName.length())
            fileName = fileName + ".txt";

        list.open(fileName);
        list >> Nodes;
        list >> Edges;

        cout << endl
             << "1. Lista krawdzi | 2. Macierz sasiedztwa" << endl;
        int graphType;
        cin >> graphType;
        switch (graphType)
        {
        case 1:
        {
            for (int i = 0; i < Edges; i++)
            {
                list >> x >> y;
                AddEdge(EdgeList, x, y);
                AddEdge(EdgeList, y, x);
            }
            NoDuplicates(EdgeList);
            ShowEdgeList(EdgeList);
            connection(EdgeListToMatrix(EdgeList, Nodes), Nodes);
            break;
        }

        case 2:
        {
            int **Matrix = new int *[Nodes];
            for (int i = 0; i < Nodes; i++)
            {
                Matrix[i] = new int[10];
                for (int j = 0; j < Nodes; j++)
                    Matrix[i][j] = 0;
            }

            for (int i = 0; i < Nodes; i++)
            {
                list >> x >> y;
                Matrix[x][y] = 1;
                Matrix[y][x] = 1;
            }
            ShowMatrixGraph(Matrix, Nodes);
            connection(Matrix, Nodes);
        }
        break;
        default:
            break;
        }
        break;
    }
    case 2:

        cout << endl
             << "Wpisz liczbe wierzcholkow" << endl;
        cin >> Nodes;
        cout << "Wpisz liczbe krawedzi" << endl;
        cin >> Edges;

        cout << endl
             << "1. Lista krawdzi | 2. Macierz sasiedztwa" << endl;
        int graphType;
        cin >> graphType;
        switch (graphType)
        {
        case 1:
        {
            cout << "Wpisz krawedzie: " << endl;
            for (int i = 0; i < Edges; i++)
            {
                cin >> x >> y;
                AddEdge(EdgeList, x, y);
                AddEdge(EdgeList, y, x);
            }
            NoDuplicates(EdgeList);
            ShowEdgeList(EdgeList);
            connection(EdgeListToMatrix(EdgeList, Nodes), Nodes);
            break;
        }

        case 2:
        {
            int **Matrix = new int *[Nodes];
            for (int i = 0; i < Nodes; i++)
            {
                Matrix[i] = new int[10];
                for (int j = 0; j < Nodes; j++)
                    Matrix[i][j] = 0;
            }

            for (int i = 0; i < Edges; i++)
            {
                cin >> x >> y;
                Matrix[x][y] = 1;
                Matrix[y][x] = 1;
            }
            ShowMatrixGraph(Matrix, Nodes);
            connection(Matrix, Nodes);
        }
        break;
        default:
            break;
        }
    default:
        break;
    }
}