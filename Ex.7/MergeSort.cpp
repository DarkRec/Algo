#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

struct node
{
    int val;
    node* next;
};

void Add(node*& H, int x)
{
    node* p = new node;
    p->next = H;
    p->val = x;
    H = p;
};

void Show(node* H)
{
    cout << "H->";
    node* p = H;
    while (p != NULL)
    {

        cout << "(" << p->val << ")->";
        p = p->next;
    }
    cout << "NULL" << endl;
}

void Split(node*& H, node*& H1, node*& H2)
{
    if (H != NULL && H->next != NULL)
    {
        node* p = H;
        node* e = H;
        int count = 0;
        while (p->next != NULL)
        {
            count++;
            p = p->next;
        }
        H1 = e;
        for (int i = 0; i < count / 2; i++)
        {
            e = e->next;
        }
        H2 = e->next;
        e->next = NULL;
    }
}

void AddAndShift(node*& tail, node*& src)
{
    node* next_src = src->next;
    tail->next = src;
    tail = tail->next;
    src = next_src;
}

node* Merge(node* H1, node* H2) 
{

    if (H1 == NULL) {
        return H2;
    }
    if (H2 == NULL) {
        return H1;
    }

    node* head;
    if (H1->val < H2->val) {
        head = H1;
        H1 = H1->next;
    }
    else {
        head = H2;
        H2 = H2->next;
    }

    node* p = head;
    while (H1 != NULL && H2 != NULL) {
        if (H1->val < H2->val) {
            p->next = H1;
            H1 = H1->next;
        }
        else {
            p->next = H2;
            H2 = H2->next;
        }
        p = p->next;
    }

    if (H1 == NULL) {
        p->next = H2;
    }
    else {
        p->next = H1;
    }

    return head;
}

void MS(node*& H)
{
    if (H && H->next)
    {
        node* H1 = NULL;
        node* H2 = NULL;
        Split(H, H1, H2);
        H = NULL;
        MS(H1);
        MS(H2);
        H = Merge(H1, H2);
    }
}

int main()
{
    node* H = NULL;
    srand(time(NULL));
    int size = 11;
    for (int i = 0; i < size; i++) {
        Add(H, rand() % 100);
    }
    Show(H);
    MS(H);
    Show(H);
    return 0;
}
