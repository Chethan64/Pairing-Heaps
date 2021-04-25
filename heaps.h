#include <bits/stdc++.h>
using namespace std;

class pairingHeap {
    private:
        typedef struct node {
            int data;
            struct node* left;
            struct node* right;
        } node;

        int size_;
        node* root_;
        
        node* make_node(int data) const;
        void display_wrapper(node* root) const;
        void destroy_heap(node* root);
        node* merge_node(node* node1, node* node2);
        pairingHeap(node* root):size_(0), root_(root) {}
        
    public:
        pairingHeap():size_(0), root_(nullptr) {}
        ~pairingHeap();
        bool is_empty() const;
        void display() const;
        void insert(int data);
        int find_min() const;
        void merge(pairingHeap& pair1);
        int extract_minimum();
        int size();
};
