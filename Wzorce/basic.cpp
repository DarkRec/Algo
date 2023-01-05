#include <iostream>
#include <string>
#include <cstdlib>
#include <time.h>

const int T = 60;
const int P = 3;

using namespace std;

string text()
{
    string t = "";
    for (int i = 0; i < T; i++)
        t += char('A' + (rand() % 3));

    return t;
}

string pattern()
{
    string p = "";
    for (int i = 0; i < P; i++)
        p += char('A' + (rand() % 3));

    return p;
}

int wyszukiwanie_naiwne(string t, string p)
{
    int counter = 0;
    for (int i = 0; i <= T - P; i++)
    {
        if (p == t.substr(i, 3))
        {
            cout << "^";
            counter++;
        }
        else
            cout << " ";
    }
    cout << endl;
    return counter;
}

int PrefSuf(string t)
{
    int PI[T + 1], x;
    PI[0] = x = -1;
    for (int i = 1; i <= T; i++)
    {
        while ((x > -1) && (t[x] != t[i - 1]))
            x = PI[x];
        PI[i] = x;
        x++;
    }
    return x;
}

int main()
{
    srand((unsigned)time(NULL));

    string t = text();
    string p = pattern();

    cout << p << endl;
    cout << t << endl;

    cout << "Ilosc powtorzen wzorca w tekscie:  " << wyszukiwanie_naiwne(t, p) << endl;

    cout << "Najdluzszy Prefikso-Sufiks:  " << PrefSuf(t) << " | " << t.substr(0, PrefSuf(t)) << endl;

    return 0;
}