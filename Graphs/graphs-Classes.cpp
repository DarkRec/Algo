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

const string FILENAME = "graf.txt";

//======================

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

//========================================
//   _   _   _   _   _   _
//  / \ / \ / \ / \ / \ / \ 
// ( M | A | T | R | I | X )
//  \_/ \_/ \_/ \_/ \_/ \_/

class Macierz
{
public:
    int **Matrix;
    int size;
    Macierz()
    {
        fstream matrix; // Macierz z pliku
        matrix.open(FILENAME);
        matrix >> size;
        Matrix = new int *[size];

        for (int i = 0; i < size; i++)
        {
            Matrix[i] = new int[5];

            for (int j = 0; j < size; j++)
                matrix >> Matrix[i][j];
        }

        matrix.close();
    }
    Macierz(int **MS, int msize)
    {
        Matrix = MS;
        size = msize;
    }

    void Show();        // print matrix
    edge *ToEdgeList(); // convert matrix to edge list
    node **ToList();    // convert matrix to array of lists
};

void Macierz::Show() // print matrix
{
    cout << endl;
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
            cout << Matrix[i][j] << " ";
        cout << endl;
    }
}

edge *Macierz::ToEdgeList() // convert matrix to edge list
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

node **Macierz::ToList() // convert matrix to array of lists
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

//========================================
//   _   _   _   _   _   _   _   _
//  / \ / \ / \ / \ / \ / \ / \ / \ 
// ( E | D | G | E | L | I | S | T )
//  \_/ \_/ \_/ \_/ \_/ \_/ \_/ \_/

class ListaKrawedzi
{
public:
    edge *EdgeList;
    int size;
    ListaKrawedzi()
    {
        fstream edgelist; // lista krawędzi z pliku
        edgelist.open(FILENAME);
        edgelist >> size;

        EdgeList = NULL;
        int dist;
        for (int i = 0; i < size; i++)
            for (int j = 0; j < size; j++)
            {
                edgelist >> dist;
                if (dist != 0)
                    AddEdge(EdgeList, i, j, dist);
            }
        edgelist.close();
    }
    ListaKrawedzi(edge *EL, int esize) : EdgeList(EL), size(esize)
    {
    }

    void Show();
    int Length();
    int **ToMatrix();
    node **ToList();
};

void ListaKrawedzi::Show() // print edge list
{
    cout << endl;
    edge *p = EdgeList;
    while (p)
    {
        cout << endl
             << "( " << p->from << " / " << p->to << " / " << p->dist << " )";
        p = p->next;
    }
    cout << endl;
}

int ListaKrawedzi::Length()
{
    edge *p = EdgeList;
    int len = 0;
    while (p)
    {
        len += p->dist;
        p = p->next;
    }
    return len;
}

int **ListaKrawedzi::ToMatrix() // convert edgelist to matrix
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

node **ListaKrawedzi::ToList() // convert edgelist to matrix  --  EdgeListToList
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

//========================================
//   _   _   _   _
//  / \ / \ / \ / \ 
// ( L | I | S | T )
//  \_/ \_/ \_/ \_/

class Lista
{
public:
    int size;
    node **List;
    Lista()
    {
        fstream file; // lista z pliku
        file.open(FILENAME);
        file >> size;
        List = new node *[size];
        for (int i = 0; i < size; i++)
            List[i] = NULL;

        int dist;
        for (int i = 0; i < size; i++)
            for (int j = 0; j < size; j++)
            {
                file >> dist;
                if (dist != 0)
                    Add(List[i], j, dist);
            }
        file.close();
    }
    Lista(node **LS, int lsize) : List(LS), size(lsize)
    {
    }

    void Show();
    int **ToMatrix();
    edge *ToEdgeList();
};

void Lista::Show() // print array of lists
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

int **Lista::ToMatrix() // convert array of lists to matrix
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

edge *Lista::ToEdgeList() // convert list to edge list
{
    edge *EdgeList = NULL;
    for (int i = 0; i < size; i++)
    {
        node *p = List[i];
        while (p)
        {
            AddEdge(EdgeList, i, p->to, p->dist);
            p = p->next;
        }
    }
    return EdgeList;
}

//========================================
//   _   _   _   _   _   _   _
//  / \ / \ / \ / \ / \ / \ / \ 
// ( K | r | u | s | k | a | l )
//  \_/ \_/ \_/ \_/ \_/ \_/ \_/

void Del(edge *&H)
{
    if (H != NULL)
    {
        edge *p = H;
        H = p->next; // H = H->next
        delete p;
    }
}

void Swap(edge *&H)
{
    if (H && H->next)
    {
        edge *e = H->next;
        H->next = H->next->next;
        e->next = H->next->next;
        H->next->next = e;
    }
}

void BubbleSort(edge *&H)
{
    if (H != NULL && H->next != NULL)
    {
        edge *last = NULL;
        edge *p = H;
        while (p->next != last)
        {
            edge *p = H;
            while (p->next->next != last)
            {
                if (p->next->dist > p->next->next->dist)
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

void NoDuplicates(edge *&H)
{
    edge *p, *q, *dup;
    p = H;
    while (p != NULL && p->next != NULL)
    {
        q = p;
        while (q->next != NULL)
        {
            if (p->from == q->next->to && p->to == q->next->from)
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

void FarSwap(edge *p, edge *e)
{
    edge *b = e->next->next;
    edge *a = p->next;
    p->next = e->next;
    e->next = a;
    p->next->next = a->next;
    a->next = b;
}

edge *CombSort(edge *H, int gap)
{
    if (gap == 0)
        gap = 1;
    if (gap > 1)
    {
        if (gap == 9 || gap == 10)
            gap = 11;

        edge *e = H;
        edge *b = H;
        for (int n = 0; n < gap; n++)
        {
            e = e->next;
        }
        while (e->next)
        {
            if (b->next->dist > e->next->dist)
            {
                FarSwap(e, b);
            }
            e = e->next;
            b = b->next;
        }
        CombSort(H, gap / 1.3 - 1);
    }
    else if (gap == 1)
    {
        Del(H);
        BubbleSort(H);
        return H;
    }
}

edge *CombSortStart(edge *H)
{
    edge *p = H;
    int n = 0;
    while (p)
    {
        p = p->next;
        n++;
    }
    AddEdge(H, 0, 0, 0);
    return CombSort(H, n - 1);
}

//====================

edge *Kruskal(edge *List, int size)
{
    edge *Kruskal = NULL;
    int forest = 1;

    int *Color = new int[5];
    int *Forest = new int[5];

    for (int i = 0; i < size; i++)
    {
        Color[i] = 0;
        Forest[i] = 0;
    }

    cout << endl;
    while (List != NULL)
    {
        if (Color[List->from] == 0 && Color[List->to] == 0)
        {
            Forest[List->from] = forest;
            Forest[List->to] = forest;
            Color[List->from] = 1;
            Color[List->to] = 1;
            forest++;
            AddEdge(Kruskal, List->from, List->to, List->dist);
        }
        else if (Color[List->from] == 0 && Color[List->to] == 1)
        {
            Color[List->from] = 1;
            Forest[List->from] = Forest[List->to];
            AddEdge(Kruskal, List->from, List->to, List->dist);
        }
        else if (Color[List->from] == 1 && Color[List->to] == 0)
        {
            Color[List->to] = 1;
            Forest[List->to] = Forest[List->from];
            AddEdge(Kruskal, List->from, List->to, List->dist);
        }
        else if (Color[List->from] == 1 && Color[List->to] == 1 && Forest[List->from] != Forest[List->to])
        {
            int las1 = Forest[List->from];
            int las2 = Forest[List->to];
            for (int i = 0; i < size; i++)
            {
                if (Forest[i] == las1 || Forest[i] == las2)
                    Forest[i] = forest;
            }
            forest++;
            AddEdge(Kruskal, List->from, List->to, List->dist);
        }
        Del(List);
    }

    class ListaKrawedzi Kr(Kruskal, size);
    cout << "Length: " << Kr.Length() << endl;
    // return Kr;
    return Kruskal;
}

//========================================
//   _   _   _   _
//  / \ / \ / \ / \ 
// ( P | r | i | m )
//  \_/ \_/ \_/ \_/

node *SearchMax(node *List, int *Color)
{
    node *p = List;
    node *max = new node;
    max->dist = 0;
    while (p)
    {
        if (max->dist < p->dist && Color[p->to] == 0)
            max = p;
        p = p->next;
    }
    if (max->dist == 0)
        return NULL;

    return max;
}

node *SearchMin(node *List, int *Color)
{
    node *p = List;
    node *max = SearchMax(List, Color);
    if (max == NULL)
        return NULL;

    node *min = max;
    for (int i = 0; p; i++, p = p->next)
        if (min->dist > p->dist && Color[p->to] == 0)
            min = p;

    return min;
}

int EdgeListLength(edge *EdgeList)
{
    edge *p = EdgeList;
    int size = 0;
    while (p)
    {
        size++;
        p = p->next;
    }
    return size;
}

//====================

edge *Prim(node **List, int size, int start)
{
    edge *prim = NULL;
    int *Color = new int[10];

    for (int i = 0; i < size; i++)
        Color[i] = 0;
    Color[start] = 1;

    node *min = SearchMin(List[start], Color);
    Color[min->to] = 1;
    AddEdge(prim, start, min->to, min->dist);

    while (EdgeListLength(prim) != size - 1)
    {
        node *MIN = new node;
        MIN->dist = 0;
        int pos;
        node *MinList = NULL;
        for (int i = 0; i < size; i++)
        {
            if (Color[i] == 1)
            {
                node *NewMin = SearchMin(List[i], Color);
                if (NewMin == NULL)
                    continue;
                if (MIN->dist > NewMin->dist || MIN->dist == 0)
                {
                    MIN = NewMin;
                    pos = i;
                }
            }
        }
        Color[MIN->to] = 1;
        AddEdge(prim, pos, MIN->to, MIN->dist);
    }
    return prim;
}

//========================================

int main()
{

    class Lista listGraph;
    listGraph.Show();

    // class Macierz matrixGraph(listGraph.ToMatrix(), listGraph.size);
    class Macierz matrixGraph;
    matrixGraph.Show();

    // class ListaKrawedzi edgeListGraph(matrixGraph.ToEdgeList(), matrixGraph.size);
    class ListaKrawedzi edgeListGraph;
    edgeListGraph.Show();

    // edgeListGraph.EdgeList = CombSortStart(edgeListGraph.EdgeList);
    // Kruskal(edgeListGraph.EdgeList, edgeListGraph.size);

    // Prim(edgeListGraph.ToList(), edgeListGraph.size, 0);
}