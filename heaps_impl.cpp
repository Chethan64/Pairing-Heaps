#include "heaps.h"

pairingHeap::node* pairingHeap::make_node(int data) const
{
    node* temp = (node*)malloc(sizeof(node));
    temp->data = data;
    temp->left = nullptr;
    temp->right = nullptr;
    return temp;
}

pairingHeap::~pairingHeap()
{
    this->destroy_heap(this->root_);
    this->root_ = nullptr;
}

void pairingHeap::destroy_heap(node* root)
{
    if(root == nullptr)
        return;

    if(root->left != nullptr)
    {
        destroy_heap(root->left);
        root->left = nullptr;
    }

    if(root->right != nullptr)
    {
        destroy_heap(root->right);
        root->right = nullptr;
    }
    
    free(root);
}

int pairingHeap::find_min() const
{
    return this->root_->data;
}

bool pairingHeap::is_empty() const
{
    return this->root_ == nullptr;
}

void pairingHeap::merge(pairingHeap& heap1)
{
    if(this->root_ == nullptr)
    {
        this->root_ = heap1.root_;
        return;
    }

    if(heap1.root_ == nullptr)
        return;

    if(this->root_->data < heap1.root_->data)
    {
        node* temp = this->root_->left;
        this->root_->left = heap1.root_;
        heap1.root_->right = temp;
    }
    else
    {
        node* temp = heap1.root_->left;
        heap1.root_->left = this->root_;
        this->root_->right = temp;
        root_ = heap1.root_;
    }
}

void pairingHeap::insert(int data)
{
    node* temp = make_node(data);
    this->root_ = merge_node(this->root_, temp);
    this->size_++;
}

pairingHeap::node* pairingHeap::merge_node(node* node1, node* node2)
{
    if(node1 == nullptr)
        return node2;

    if(node1->data < node2->data)
    {
        node* temp_node = node1->left;
        node1->left = node2;
        node2->right = temp_node;
        return node1;
    }
    else
    {
        node* temp_node = node2->left;
        node2->left = node1;
        node1->right = temp_node;
        return node2;
    }
}

int pairingHeap::size()
{
    return this->size_;
}

int pairingHeap::extract_minimum()
{
    node* root = this->root_;
    node* pairs = nullptr;
    node* temp = root->left;
    node* new_root = nullptr;

    if(temp == nullptr)
    {
        int data = root_->data;
        this->root_ = new_root;
        free(root);
        return data;
    }        
    
    // left to right
    while((temp != nullptr) && (temp->right != nullptr))
    {
        node* next_pair = temp->right->right;        
        node* temp_node = merge_node(temp,temp->right);
        temp_node->right = pairs;
        pairs = temp_node;
        temp = next_pair;
    }

    if(temp != nullptr)
    {
        temp->right = pairs;
        pairs = temp;
    }

    // right to left
    temp = pairs;
    if(temp->right == nullptr)
    {
        new_root = temp;
        temp = nullptr;
    }
    else
    {
        node* temp_node = temp;
        temp = temp->right->right;
        new_root = merge_node(temp_node,temp_node->right);
    }

    while(temp != nullptr)
    {
        new_root = merge_node(new_root,temp);
        temp = temp->right;
    }

    this->root_ = new_root;
    int data = root_->data;
    free(root);
    return data;
}

void pairingHeap::display_wrapper(node* root) const
{
    if(root == nullptr)
        return;

    cout << root->data;
    node* temp = root;

    if(temp->right != nullptr)
    {
        temp = temp->right;
        cout << "\t";
        display_wrapper(temp);
    }

    temp = root;
    if(temp->left != nullptr)
    {
        temp = temp->left;
        cout << "\n";
        display_wrapper(temp);
    }
    return;
}

void pairingHeap::display() const
{
    display_wrapper(this->root_);
    cout << "\n";
}

