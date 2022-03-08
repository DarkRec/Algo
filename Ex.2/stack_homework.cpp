#include <iostream>

using namespace std;

struct node
{
    int val;
    node *next;
};

void Show(node *H)
{
    cout << "(Top)->";
    node *p = H;
    while (p != NULL)
    {
        cout << p->val << "->";
        p = p->next;
    }
    cout << "NULL" << endl;
}

void Push(node *&H, int x)
{
    node *p = new node;
    p->next = H;
    p->val = x;
    H = p;
}

void Pop(node *&H)
{
    if (H != NULL)
    {
        node *p = H;
        H = p->next; // H = H->next
        delete p;
    }
}

node *Top(node *&H)
{
    if (H != NULL)
    {
        cout << "Top: " << H->next << endl;
        return H->next;
    }
}

bool Empty(node *&H)
{
    if (H == NULL)
        cout << "Stack is Empty" << endl;
    else
        cout << "Stack is not Empty" << endl;
    return H == NULL;
}

int main()
{
    node *T = NULL;

    Push(T, 6);
    Push(T, 8);
    Push(T, 1);
    Show(T);
    Top(T);
    Pop(T);
    Show(T);
    Empty(T);
}