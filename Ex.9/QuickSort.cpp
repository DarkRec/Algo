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

int PartitionByRight(int* t, int l, int r)  {
    int i = l;
    for (int j = l; j < r; j++) {
        if (t[j] < t[r]) {
            swap(t[i], t[j]);
            i++;
        }
    }
    swap(t[i], t[r]);
    return i;
}

int PartitionByLeft(int* t, int l, int r)   {
    int i = l, j = r + 1;
    while (true)    {
        do{
            i++;
        } while (i <= r && t[i] < t[l]);

        do{
            j--;
        } while (t[j] > t[l]);

        if (i > j)
            break;

        swap(t[i], t[j]);
    }
    swap(t[j], t[l]);
    return j;
}

int partitionMedianOf3(int* t, int l, int r) {
    int i, j, v, x;
    int mid = l + (r - l) / 2;

    if (t[l] > t[mid]) swap(t[l], t[mid]);
    if (t[l] > t[r]) swap(t[l], t[r]);
    if (t[mid] > t[r]) swap(t[mid], t[r]);

    v = t[mid]; i = l - 1; j = r + 1;
    while (true)
    {
        do {
            i++;
        } while (t[i] < v);

        do {
            j--;
        } while (t[j] > v);

        if (i >= j) {
            return j;
        }

        swap(t[i], t[j]);
    }
}

void QuickSort(int* t, int L, int R){
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

    int tab[14] = { 10, 5, 2, 3, 12, 7, 19, 5, 1, 3, 12, 6, 4, 2 };

    QuickSort(tab, 0, 13);
    cout << endl;
    for (int i = 0; i < 14; i++)
        cout << tab[i] << " ";
}
