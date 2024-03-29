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

edge *LongestRoad(edge *H)
{
    edge *p = H;
    int len = 0;
    edge *longest = NULL;
    while (p)
    {
        if (len < p->dist)
        {
            len = p->dist;
            longest = p;
        }
        p = p->next;
    }
    return longest;
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
    // ShowEdgeList(prim);
    //  cout << "Length: " << Length(prim) << endl;
    return prim;
}

//===============================================
int main()
{

    fstream matrix; // Macierz z pliku
    matrix.open("mapa.txt");

    int N, M, K;
    matrix >> N >> M >> K;

    int **NMK = new int *[N];

    for (int i = 0; i < N; i++)
    {
        NMK[i] = new int[5];

        for (int j = 0; j < M; j++)
            matrix >> NMK[i][j];
    }

    int **MS = new int *[N];

    for (int i = 0; i < N; i++)
    {
        MS[i] = new int[5];
        for (int j = 0; j < N; j++)
            MS[i][j] = 0;
    }
    for (int i = 0; i < N; i++)
    {
        MS[NMK[i][0] - 1][NMK[i][1] - 1] = NMK[i][2];
        MS[NMK[i][1] - 1][NMK[i][0] - 1] = NMK[i][2];
    }

    int **BaseMS = new int *[N];
    for (int i = 0; i < N; i++)
    {
        BaseMS[i] = new int[5];
        for (int j = 0; j < N; j++)
            BaseMS[i][j] = MS[i][j];
    }
    // cout << N << M << K;
    //  ShowMatrixGraph(NMK, N);
    //  ShowMatrixGraph(MS, N);

    // cout << endl;
    matrix.close();

    node **List = MatrixToList(MS, N);
    // ShowListGraph(List, N);
    edge *EdgeList = EdgeListFromMatrix(MS, N);
    // cout << endl;

    int superdrogi = 0;
    while (Length(Prim(List, N, 0)) >= K)
    {
        edge *longest = LongestRoad(EdgeList);
        MS[longest->from][longest->to] = 1;
        MS[longest->to][longest->from] = 1;
        List = MatrixToList(MS, N);
        EdgeList = EdgeListFromMatrix(MS, N);
        superdrogi++;
    }
    Prim(List, N, 0);
    int **EndMS = ListToMatrix(List, N);

    cout << "Zachowane Drogi: " << endl;
    for (int i = 0; i < N; i++)
    {
        for (int j = i; j < N; j++)
        {
            if (EndMS[i][j] == BaseMS[i][j] && EndMS[i][j] != 0)
                cout << "(" << i + 1 << "," << j + 1 << "," << EndMS[i][j] << ")" << endl;
        }
    }
    cout << endl
         << "Liczba superdrog: " << superdrogi << endl;
}