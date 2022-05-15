#include <iostream>
#include <ctime>
#define SIZE 20

using namespace std;

void show(int *t)
{
    for (int i = 1; i < SIZE; i++)
        cout << t[i] << ",";
    cout << endl;
}
void heapify(int n, int heapsize, int *t)
{
    int largest;
    int l = 2 * n;
    int r = (2 * n) + 1;
    if (l <= heapsize && t[l] > t[n])
        largest = l;
    else
        largest = n;
    if (r <= heapsize && t[r] > t[largest])
        largest = r;
    if (largest != n)
    {
        swap(t[n], t[largest]);
        heapify(largest, heapsize, t);
    }
}
void build_heap(int heapsize, int *t)
{
    for (int i = heapsize / 2; i > 0; i--)
        heapify(i, heapsize, t);
}

void heap_sort(int size, int *t)
{
    int heapsize = size;
    build_heap(heapsize, t);
    for (int i = heapsize - 1; i > 1; i--)
    {
        swap(t[1], t[i]);
        heapify(1, i - 1, t);
    }
}

int main()
{
    srand(time(NULL));
    int tab[SIZE];

    for (int i = 1; i < SIZE; i++)
        tab[i] = rand() % 100;
    show(tab);

    heap_sort(SIZE, tab);
    cout << endl;
    show(tab);
}