#include <iostream>

using namespace std;

struct node
{
    int val;
    node *next;
};

void Add(node *&H, int x)
{
    node *p = new node;
    p->next = H;
    p->val = x;
    H = p;
};

void Show(node *H)
{
    cout << "H->";
    node *p = H;
    while (p != NULL)
    {

        cout << p->val << "->";
        p = p->next;
    }
    cout << "NULL" << endl;
}

void Delete(node *&H)
{
    if (H != NULL)
    {
        node *p = H;
        H = p->next;
        delete p;
    }
}

node *Reverse(node *&H)
{
    if (H != NULL)
    {
        node *p = H;
        node *e = NULL;
        node *R = NULL;
        while (p != NULL)
        {
            e = p->next;
            p->next = R;
            R = p;
            p = e;
        }
        return R;
    }
}

node *Reverse_clone(node *&H)
{
    if (H != NULL)
    {
        node *R = NULL;
        node *p = H;
        while (p != NULL)
        {
            Add(R, p->val);
            p = p->next;
        }
        return R;
    }
}

node *Clone(node *&H)
{
    node *A = Reverse_clone(H);
    A = Reverse(A);
    return A;
}

void Delete_even(node *&H)
{
    Add(H, 0);
    if (H->next != NULL)
    {
        node *p = H;
        while (p->next)
        {
            if (p->next->val % 2 == 0)
            {
                Delete(p->next);
            }
            else
            {
                p = p->next;
            }
        }
        Delete(H);
    }
}

/*
void Delete_two_sum_even(node *&H)
{
    Add(H, 0);
    if (H->next && H->next->next)
    {
        node *p = H;
        while (p->next->next && p->next->next->next)
        {
            if ((p->next->val + p->next->next->val) % 2 == 0)
            {
                p->next = p->next->next->next;
            }
            else
            {
                p = p->next;
                p = p->next;
            }
        }
        if (p->next->next != NULL && p->next->next->next == NULL && (p->next->val + p->next->next->val) % 2 == 0)
            p->next = NULL;
        H = H->next;
    }
}
*/

void Delete_two_sum_even(node *&H)
{
    Add(H, 0);
    if (H->next && H->next->next)
    {
        node *p = H;
        while (p->next && p->next->next)
        {
            if ((p->next->val + p->next->next->val) % 2 == 0)
            {
                Delete(p->next);
                Delete(p->next);
            }
            else
            {
                p = p->next->next;
            }
        }
        Delete(H);
    }
}

void Add_copy_to_end(node *&H)
{
    node *R = new node;
    R = Reverse_clone(H);
    Show(R);
    if (H != NULL)
    {
        node *p = H;
        while (p != NULL)
        {
            cout << p->val << "->";
            p = p->next;
        }
        cout << "NULL" << endl;
    }
}

node *Connect_lists(node *&H)
{
    if (H != NULL)
    {
        node *A = Reverse_clone(H);
        node *p = H;
        while (p->next != NULL)
        {
            p = p->next;
        }
        p->next = A;
        A = H;
        return A; // return H
    }
}

/*
node *Reverse_Connect_lists(node *&H, node *&A)
{
    if (H != NULL)
    {
        Connect_lists(A, H);
    }
}*/

node *Reverse_Connect_lists(node *&H)
{
    if (H != NULL)
    {
        node *A = Reverse_clone(H);
        node *e = H;
        H = A;
        node *p = H;
        while (p->next != NULL)
        {
            p = p->next;
        }
        p->next = e;
        return H;
    }
}

void AddToEnd(node *&H, int x)
{
    node *p = H;
    while (p->next)
    {
        p = p->next;
    }
    node *e = new node;
    e->val = x;
    e->next = NULL;
    p->next = e;
}

node *Add_sum_to_end(node *&H)
{
    if (H != NULL)
    {
        Add(H, 0);
        node *p = H;
        node *Sum = NULL;
        while (p->next && p->next->next)
        {
            AddToEnd(Sum, (p->next->val + p->next->next->val));
            p = p->next->next;
        }
        p->next = Sum;
        H = H->next;
        return H;
    }
}

int main()
{
    node *H = NULL;
    /*
    Add(H, 5);
    Add(H, 1);
    Add(H, 8);
    Add(H, 4);
    Add(H, 3);
    Add(H, 1);
    */
    Add(H, 2);
    Add(H, 5);
    Add(H, 3);
    Add(H, 1);
    Show(H);
    // Delete_even(H);
    // Delete_two_sum_even(H);
    // Show(H);
    //  node *A = Clone_list(H);
    //  node *R = Reverse_clone(H);
    //  Show(R);
    // node *Con = Connect_lists(H);
    // node *Con = Reverse_Connect_lists(H);
    // Show(Con);
    node *Aste = Add_sum_to_end(H);
    Show(Aste);
    // Add_copy_to_end(H);
}
