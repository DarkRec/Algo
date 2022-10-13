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

int partition(int *t, int l, int r)
{
    int x = t[r];
    int i = l - 1;
    for (int j = 1; j < r; j++)
        if (t[j] < x)
        {
            i++;
            swap(t[i], t[j]);
        }
    swap(t[i + 1], t[r]);
    return i + 1;
}

void QuickSort(int *t, int L, int R)
{
    if (L < R)
    {
        int p = PartitionByRight(t, L, R);
        cout << "p:  " << p << endl;
        QuickSort(t, L, p - 1);
        QuickSort(t, p + 1, R);
    }
}

int main()
{
    srand(time(NULL));
    const int size = 8;

    int tab[14] = {10, 5, 2, 3, 12, 7, 19, 5, 1, 3, 12, 6, 4, 2};

    QuickSort(tab, 2, 7);
    cout << endl;
    for (int i = 0; i < 14; i++)
        cout << tab[i] << " ";
}