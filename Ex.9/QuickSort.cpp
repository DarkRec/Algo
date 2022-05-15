#include <iostream>
#include <ctime>

using namespace std;

// zaimplementować skrajnie lewy,
// zaimplementować skrajnie prawy
// zaimplementować w oparciu o mediane z trzech
// Swap(a[L+1],a[L+R>>1])
// if (a[L+1]>a[R]) swap(a[L+1],a[R])
// if (a[L]>a[R]) swap(a[L],a[R])
// Zaimplementować sortowanie hybrydowe

int PartitionByRight(int *t, int l, int r)
{
    int i = l;
    for (int j = l; j < r; j++)
    {
        if (t[j] < t[r])
        {
            swap(t[i], t[j]);
            i++;
        }
    }
    swap(t[i], t[r]);
    return i;
}

int PartitionByLeft(int *t, int l, int r)
{
    int i = l, j = r + 1;
    while (true)
    {
        do
        {
            i++;
        } while (i <= r && t[i] < t[l]);
        do
        {
            j--;
        } while (t[j] > t[l]);
        if (i > j)
            break;
        swap(t[i], t[j]);
    }
    swap(t[j], t[l]);
    return j;
}

void QuickSort(int *t, int L, int R)
{
    if (L < R)
    {
        int p = PartitionByRight(t, L, R);
        QuickSort(t, L, p - 1);
        QuickSort(t, p + 1, R);
    }
}

int main()
{
    srand(time(NULL));
    const int size = 8;

    int tab[size];
    for (int i = 0; i < size; i++)
    {
        tab[i] = rand() % 100;
    }
    QuickSort(tab, 0, size - 1);
    cout << endl;
    for (int i = 0; i < size; i++)
        cout << tab[i] << " ";
}