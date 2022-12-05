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

//===============================================

class Macierz
{
public:
    int **MS;
    int Msize;
    Macierz(int **Matrix, int size) : MS(Matrix), Msize(size)
    {
    }

    edge *ToEdgeList() // convert matrix to edge list
    {
        edge *List = NULL;
        int count = 0;
        for (int i = 0; i < Msize; i++)
        {
            for (int j = 0; j < Msize; j++)
                if (MS[i][j] != 0)
                {
                    AddEdge(List, i, j, MS[i][j]);
                    count++;
                }
        }
        return List;
    }

    Show() // print matrix
    {
        cout << endl;
        for (int i = 0; i < Msize; i++)
        {
            for (int j = 0; j < Msize; j++)
                cout << MS[i][j] << " ";
            cout << endl;
        }
    }
    node **MatrixToList() // convert matrix to array of lists
    {
        node **LS = new node *[Msize];
        for (int i = 0; i < Msize; i++)
            LS[i] = NULL;

        int dist;
        for (int i = 0; i < Msize; i++)
            for (int j = 0; j < Msize; j++)
            {
                dist = MS[i][j];
                if (dist != 0)
                    Add(LS[i], j, dist);
            }
        return LS;
    }
};

//===============================================

class ListaKrawedzi
{
public:
    int Esize, Edist;
    edge *EdgeList = NULL;
    ListaKrawedzi()
    {
        fstream edgelist; // lista krawędzi z pliku
        edgelist.open("graf.txt");
        edgelist >> Esize;

        for (int i = 0; i < Esize; i++)
            for (int j = 0; j < Esize; j++)
            {
                edgelist >> Edist;
                if (Edist != 0)
                    AddEdge(EdgeList, i, j, Edist);
            }
    }

    Show() // print edge list
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

    node **ToList() // convert edgelist to matrix  --  EdgeListToList
    {
        edge *p = EdgeList;
        node **LS = new node *[Esize];
        for (int i = 0; i < Esize; i++)
            LS[i] = NULL;

        for (int i = 0; i < Esize; i++)
            for (int j = 0; j < Esize; j++)
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
};

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

void Print(int *tab, int size)
{
    for (int i = 0; i < size; i++)
        cout << tab[i] << " ";
    cout << "\t";
}

int Length(edge *H)
{
    edge *p = H;
    int len = 0;
    while (p)
    {
        len += p->dist;
        p = p->next;
    }
    return len;
}

//===============================================

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

edge *EdgeListFromList(node **List, int size) // convert list to edge list
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

//===============================================

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

//===============================================

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

    cout << "Length: " << Length(Kruskal) << endl;
    return Kruskal;
}

//===============================================
int main()
{

    fstream list; // lista z pliku
    list.open("graf.txt");
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
    list.close();

    ShowListGraph(LS, Lsize);

    // edge *EdgeList = EdgeListFromList(LS, Lsize);
    // EdgeList = CombSortStart(EdgeList);
    // Kruskal(EdgeList, Lsize);

    int Msize;
    int **MS = new int *[Msize];

    fstream matrix; // Macierz z pliku
    matrix.open("graf.txt");
    matrix >> Msize;

    for (int i = 0; i < Msize; i++)
    {
        MS[i] = new int[5];

        for (int j = 0; j < Msize; j++)
            matrix >> MS[i][j];
    }
    matrix.close();
    class Macierz ms(MS, Msize);

    ms.Show();
    edge *a;
    a = ms.ToEdgeList();
}