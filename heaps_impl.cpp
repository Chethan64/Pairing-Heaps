#include "heaps.h"

node* make_node(int data)
{
    node* temp = (node*)malloc(sizeof(node));
    temp->data = data;
    temp->left = nullptr;
    temp->right = nullptr;
    return temp;
}

int& find_min(node* heap)
{
    return heap->data;
}

bool is_empty(node* heap)
{
    return heap == nullptr;
}

node* merge(node* heap1, node* heap2)
{
    if(heap1 == nullptr)
        return heap2;

    if(heap2 == nullptr)
        return heap1;

    if(heap1->data < heap2->data)
    {
        node* temp = heap1->left;
        heap1->left = heap2;
        heap2->right = temp;
        return heap1;
    }
    else
    {
        node* temp = heap2->left;
        heap2->left = heap1;
        heap1->right = temp;
        return heap2;
    }
}

node* insert(node* heap, int data)
{
    node* temp = make_node(data);
    node* new_root = merge(heap,temp);
    return new_root;
}

void display(node* heap)
{
    cout << heap->data;
    node* temp = heap;

    if(temp->left != nullptr)
    {
        temp = temp->left;
        cout << "\n";
        display(temp);
    }
    temp = heap;
    if(temp->right != nullptr)
    {
        temp = temp->right;
        cout << "\t";
        display(temp);
    }
    return;
}
