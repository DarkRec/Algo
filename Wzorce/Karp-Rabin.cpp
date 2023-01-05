#include <iostream>
#include <string>
#include <cstdlib>
#include <time.h>

using namespace std;

const int T = 79;    // długość tekstu
const int P = 4;     // długość wzorca
const int abcP = 65; // początek alfabetu
const int abcK = 66; // koniec alfabetu

// Funkcja obliczająca hasz dla łańcucha x
//----------------------------------------
int Hash(string &x)
{
    int hx = 0;
    for (int i = 0; i < P; i++)
        hx = 3 * hx + (x[i] - 65);
    return hx;
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

void KR(string t, string p)
{
    int Hp = Hash(p);
    int Hs = Hash(t);
    int pos = 0;
    int i = 0;

    while (true)
    {
        if ((Hp == Hs) && (p == t.substr(i, P)))
        {
            while (pos < i)
            {
                cout << " ";
                pos++;
            }
            cout << "^"; // miejsce wystąpienia wzorca
            pos++;
        }
        i++;
        if (i == T - P)
            break;
        Hs = (Hs - (t[i - 1] - 65) * 27) * 3 + t[i + P - 1] - 65;
    }
}

int main()
{
    srand((unsigned)time(NULL));

    string p = pattern();
    string t = text();

    cout << p << endl;
    cout << t << endl;

    KR(t, p);
    return 0;
}