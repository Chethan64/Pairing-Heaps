#include <bits/stdc++.h>
using namespace std;

typedef struct node {
    int data;
    struct node* left;
    struct node* right;
} node;

node* make_node(int data);
int& find_min(node* heap);
bool is_empty(node* heap);
node* merge(node* heap1, node* heap2);
node* insert(node* heap, int data);
void display(node* heap);