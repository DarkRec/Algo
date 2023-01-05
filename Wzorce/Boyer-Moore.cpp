#include <iostream>
#include <string>
#include <cstdlib>
#include <time.h>

using namespace std;

const int T = 79;    // długość tekstu
const int P = 5;     // długość wzorca
const int abcP = 65; // początek alfabetu
const int abcK = 66; // koniec alfabetu

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

void BM(string t, string p)
{
    int Last[abcK - abcP + 1];

    for (int i = 0; i <= abcK - abcP; i++)
        Last[i] = -1;
    for (int i = 0; i < P; i++)
        Last[p[i] - abcP] = i;

    int pos;
    int x = pos = 0, y;
    while (x <= T - P)
    {
        y = P - 1;
        while (y > -1 && p[y] == t[x + y])
            y--;
        if (y == -1)
        {
            while (pos < x)
            {
                cout << " ";
                pos++;
            }
            cout << "^"; // miejsce wystąpienia wzorca
            pos++;
            x++;
        }
        else
            x += max(1, y - Last[t[x + y] - abcP]);
    }

    /*
    int pos = -1;
    int x = 0, y;
    while (x <= T - P)
    {
        y = P - 1;
        while (y > -1 && p[y] == t[x + y])
            y--;
        if (y > -1)
        {
            x += max(1, y - Last[t[x + y] - abcP]);
        }
        else
        {
            pos = x;
            cout << pos;
            x++;
            continue;
        }
        if (pos == -1)
            cout << -1;
    }*/
}

int main()
{
    srand((unsigned)time(NULL));

    string p = pattern();
    string t = text();

    cout << p << endl;
    cout << t << endl;

    BM(t, p);

    return 0;
}