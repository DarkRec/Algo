#include <iostream>
#include <string>
#include <cstdlib>
#include <time.h>

using namespace std;

const int T = 79; // długość tekstu
const int P = 5;  // długość wzorca

struct node
{
    int val;
    node *next;
};

struct wzorce
{
    int num;
    node *list;
};

void Add(node *&H, int x) // add node to end
{
    node *p = new node();
    p->val = x;
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

void Show(node *H)
{
    node *p = H;
    while (p)
    {
        cout << p->val << " ";
        p = p->next;
    }
}

string text()
{
    string t = "";
    for (int i = 0; i < T; i++)
        t += char('A' + (rand() % 2));

    return t;
}

string pattern()
{
    string p = "";
    for (int i = 0; i < P; i++)
        p += char('A' + (rand() % 2));

    return p;
}

int *PrefSufKMP(string p)
{
    int *PI = new int[P + 1];
    int x;
    PI[0] = x = -1;
    for (int i = 1; i <= P; i++)
    {
        while ((x > -1) && (p[x] != p[i - 1]))
            x = PI[x];
        x++;
        if ((i == P) || (p[i] != p[x]))
            PI[i] = x;
        else
            PI[i] = PI[x];
    }
    return PI;
}

wzorce *KMP(string t, string p)
{
    int *PS = PrefSufKMP(p), *search;
    int pos, x, count = 0;

    node *List = NULL;
    pos = x = 0;
    for (int i = 0; i < T; i++)
    {
        while (x > -1 && p[x] != t[i])
            x = PS[x];
        x++;
        if (x == P)
        {
            while (pos < i - x + 1)
            {
                cout << " ";
                pos++;
            }
            cout << "^"; // miejsce wystąpienia wzorca
            Add(List, pos);
            count++;
            pos++;
            x = PS[x];
        }
    }
    cout << endl;

    wzorce *wz = new wzorce;
    wz->list = List;
    wz->num = count;
    return wz;
}

int main()
{
    srand((unsigned)time(NULL));

    string p = pattern();
    string t = text();

    cout << p << endl;
    cout << t << endl;

    wzorce *wz = KMP(t, p);
    cout << endl
         << wz->num << ": ";
    Show(wz->list);

    return 0;
}