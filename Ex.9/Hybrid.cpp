#include <iostream>
#include <cstdlib>
#include <ctime>
#include <ctime>
#define size 150000

using namespace std;

void BubbleSort(int *tab, int l, int r)
{
    for (int j = size - 1; j > 0; j--)
        for (int i = l; i < r - l; i++)
        {
            // cout << tab[i] << " " << tab[i + 1] << endl;
            if (tab[i] > tab[i + 1])
            {
                swap(tab[i], tab[i + 1]);
            }
        }
}

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
void HybridQS(int *t, int L, int R)
{
    if (L < R)
    {
        if (R - L > 10)
        {
            int p = PartitionByRight(t, L, R);
            HybridQS(t, L, p - 1);
            HybridQS(t, p + 1, R);
        }
        else
            BubbleSort(t, L, R);
    }
}

void QuickSort(int *t, int L, int R)
{
    if (L < R)
    {
        int p = PartitionByRight(t, L, R);
        HybridQS(t, L, p - 1);
        HybridQS(t, p + 1, R);
    }
}

int main()
{
    srand(time(NULL));

    int tab[size];
    int tab2[size];
    int tab3[size];

    for (int i = 0; i < size; i++)
    {
        tab[i] = rand() % 100;
        tab2[i] = tab[i];
        tab3[i] = tab[i];
    }

    clock_t start = clock();
    BubbleSort(tab2, 0, size - 1);
    clock_t end = clock();
    cout << endl;

    double elapsed = double(end - start) / CLOCKS_PER_SEC;
    cout << "Bubble Sort Time: " << elapsed << " seconds.\n";

    start = clock();
    QuickSort(tab3, 0, size - 1);
    end = clock();
    cout << endl;
    elapsed = double(end - start) / CLOCKS_PER_SEC;
    cout << "Quick Sort  Time: " << elapsed << " seconds.\n";

    start = clock();
    HybridQS(tab, 0, size - 1);
    end = clock();
    cout << endl;
    elapsed = double(end - start) / CLOCKS_PER_SEC;
    cout << "Hybrid Sort Time: " << elapsed << " seconds.\n";
}
