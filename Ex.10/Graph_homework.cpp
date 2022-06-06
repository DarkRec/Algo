#include <iostream>
#include <cstdlib>
#include <fstream>

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

//===============================================

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

int **ListToMatrix(node **List, int size) // convert array of lists to matrix
{
    int **MS = new int *[size];

    for (int i = 0; i < size; i++)
    {
        MS[i] = new int[5];
        node *temp = List[i];
        for (int j = 0; j < size; j++)
        {
            if (temp->to == j)
            {
                MS[i][j] = temp->dist;
                if (temp->next)
                    temp = temp->next;
            }
            else
                MS[i][j] = 0;
        }
    }
    return MS;
}

//===============================================
edge *EdgeListFromMatrix(int **Matrix, int size) // convert matrix to edge list
{
    edge *List = NULL;
    int count = 0;
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
            if (Matrix[i][j] != 0)
            {
                AddEdge(List, i, j, Matrix[i][j]);
                count++;
            }
    }
    return List;
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

//===============================================

void ShowEdgeList(edge *EdgeList) // print edge list
{
    cout << endl;
    edge *p = EdgeList;
    while (p->next)
    {
        cout << endl
             << "( " << p->from << " / " << p->to << " / " << p->dist << " )";
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
                MS[i][j] = p->dist;
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

node **EdgeListToList(edge *EdgeList, int size) // convert edgelist to matrix
{
    edge *p = EdgeList;
    node **LS = new node *[size];
    for (int i = 0; i < size; i++)
        LS[i] = NULL;

    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
        {
            if (p->from == i && p->to == j)
            {
                Add(LS[i], j, p->dist);
                if (p->next)
                    p = p->next;
            }
        }
    return LS;
}

//===============================================
int main()
{
    //===============================================

    fstream matrix; // Macierz z pliku
    matrix.open("graf.txt");

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

    node **List = MatrixToList(MS, Msize);
    ShowListGraph(List, Msize);
    cout << endl;

    //===============================================

    fstream list; // lista z pliku
    list.open("graf3.txt");
    int Lsize;
    list >> Lsize;

    node **LS = new node *[Lsize];
    for (int i = 0; i < Lsize; i++)
        LS[i] = NULL;

    int dist;
    for (int i = 0; i < Lsize; i++)
        for (int j = 0; j < Lsize; j++)
        {
            list >> dist;
            if (dist != 0)
                Add(LS[i], j, dist);
        }

    ShowListGraph(LS, Msize);
    cout << endl;
    list.close();

    int **Matrix = ListToMatrix(LS, Lsize);
    ShowMatrixGraph(Matrix, Lsize);
    cout << endl;

    //===============================================
    fstream edgelist; // lista krawędzi z pliku
    edgelist.open("graf.txt");
    int Esize;
    edgelist >> Esize;

    edge *EdgeList = NULL;
    int Edist;
    for (int i = 0; i < Esize; i++)
        for (int j = 0; j < Esize; j++)
        {
            edgelist >> Edist;
            if (Edist != 0)
                AddEdge(EdgeList, i, j, Edist);
        }
    ShowEdgeList(EdgeList);
    edgelist.close();
    int **Matrix2 = EdgeListToMatrix(EdgeList, 5);
    cout << endl;
    ShowMatrixGraph(Matrix2, 5);

    node **List2 = EdgeListToList(EdgeList, 5);
    ShowListGraph(List2, 5);
    //===============================================

    // edge *EdgeList1 = EdgeListFromMatrix(MS, Msize);
    //  ShowEdgeList(EdgeList1);
}
// Dostaje macierz sąsiedztwa / liste sąsiedztwa
// Macierz -> Lista ✓
// Lista -> Macierz ✓
// Lista Krawędzi ✓
// Sposób czytania listy krawędzi ✓
// Generacja z listy krawędzi Listy sąsiedztwa ✓
// Generacja z Listy krawędzi Macierz sąsiedztwa ✓
// *Generacja z Macierzy Listy Krawędzi ✓