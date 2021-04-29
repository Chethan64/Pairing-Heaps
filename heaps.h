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
        node* clone_heap(node* root);
        node* merge_node(node* node1, node* node2);
        void find_wrapper(node* parent, node* child, int data, node** remove_parent);
        void inorder(node* root);  
        pairingHeap(node* root):size_(0), root_(root) {}
        
    public:
        pairingHeap():size_(0), root_(nullptr) {}
        pairingHeap(pairingHeap& heap):root_(nullptr)
        { 
            this->root_ = this->clone_heap(heap.root_); 
            this->size_ = heap.size_; 
        }
        pairingHeap& operator=(pairingHeap& rhs);
        ~pairingHeap();
        bool is_empty() const;
        void display() const;
        void insert(int data);
        int find_min() const;
        void merge(pairingHeap& pair1);
        int extract_minimum();
        int remove_element(int data);
        int size();
        void inorder_wrap();
        void flip_heap(pairingHeap& heap);
        
        template<typename InputIterator>
        void heapify(InputIterator first, InputIterator last)
        {
            while(first != last)
            {
                insert(*first++);
            }
        }   

        friend void meld(pairingHeap& heap, pairingHeap& heap1, pairingHeap& heap2);
};
