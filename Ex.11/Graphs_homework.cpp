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

void Print(int *tab, int size) // print array
{
    for (int i = 0; i < size; i++)
        cout << tab[i] << " ";
    cout << endl;
}

int Length(edge *H) // list length
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

void BubbleSort(edge *&H) // Bubblesort
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

void FarSwap(edge *p, edge *e)
{
    edge *b = e->next->next;
    edge *a = p->next;
    p->next = e->next;
    e->next = a;
    p->next->next = a->next;
    a->next = b;
}

edge *CombSort(edge *H, int gap) // Combsort
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

int **ListToMatrix(node **List, int size) // convert array of lists to matrix
{
    int **MS = new int *[size];

    for (int i = 0; i < size; i++)
    {
        MS[i] = new int[10];
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

void ShowEdgeList(edge *EdgeList) // print edge list
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

//===============================================

int **EdgeListToMatrix(edge *EdgeList, int size) // convert edgelist to matrix
{
    int **MS = new int *[size];

    edge *p = EdgeList;
    for (int i = 0; i < size; i++)
    {
        MS[i] = new int[10];
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

node *SearchMax(node *List, int *Color) // search max distance in List
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

node *SearchMin(node *List, int *Color) // search min distance in List
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

edge *Prim(node **List, int size, int start) // Prim algorithm
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
    ShowEdgeList(prim);
    cout << "Length: " << Length(prim) << endl;
    return prim;
}

//===============================================

void NoDuplicates(edge *&H) // remove duplicates ( [1/2] - [2/1])
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

edge *Kruskal(edge *List, int size) // Kruskal algorithm
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

    ShowEdgeList(Kruskal);
    cout << "Length: " << Length(Kruskal) << endl;
    return Kruskal;
}

//===============================================
int main()
{
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

    ShowListGraph(LS, Lsize);

    edge *EdgeList = EdgeListFromList(LS, Lsize);
    BubbleSort(EdgeList);
    // CombSortStart(EdgeList);
    // NoDuplicates(EdgeList);
    Kruskal(EdgeList, Lsize);

    edge *prim = Prim(LS, Lsize, 2);
}