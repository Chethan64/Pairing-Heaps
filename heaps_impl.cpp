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
    cout << "Destroying " << this << "\n";
    this->destroy_heap(this->root_);
    this->root_ = nullptr;
    delete this;
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

pairingHeap& pairingHeap::operator=(const pairingHeap& rhs)
{
    if(this != &rhs)
    {
        this->root_ = clone(rhs->root_);
        this->size_ = rhs->size_;
        delete &rhs;
    }
}

pairingHeap meld(pairingHeap& heap1, pairingHeap& heap2)
{
    if(heap1.root_ == nullptr)
    {
        pairingHeap heap(heap2);
        return heap;
    }

    if(heap2.root_ == nullptr)
    {
        pairingHeap heap(heap1);    
        return heap;
    }

    if(heap1.root_->data < heap2.root_->data)
    {
        pairingHeap* heap3 = new pairingHeap(heap1);
        pairingHeap* heap4 = new pairingHeap(heap2);
        pairingHeap::node* temp = heap3->root_->left;
        heap3->root_->left = heap4->root_;
        heap4->root_->right = temp;
        return *heap3;
    }
    else
    {
        pairingHeap* heap3 = new pairingHeap(heap1);
        pairingHeap* heap4 = new pairingHeap(heap2);
        pairingHeap::node* temp = heap4->root_->left;
        heap4->root_->left = heap3->root_;
        heap3->root_->right = temp;
        return *heap4;
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
    this->size_--;
    return data;
}

void pairingHeap::find_wrapper(node* parent, node* child, int data, node** remove_parent)
{
    if(child == nullptr)
        return;
    
    if(child->data == data)
    {
        *remove_parent = parent;
        return;
    }

    if(data > child->data)
        find_wrapper(child, child->left, data, remove_parent);
    
    find_wrapper(child, child->right, data, remove_parent);    
}    
        
int pairingHeap::remove_element(int data)
{
    node* remove_parent = nullptr;
    node* parent = nullptr;
    find_wrapper(parent, this->root_, data, &remove_parent);

    if(this->root_->data == data)
    {
        int num = extract_minimum();
        return 1;
    }

    if(remove_parent == nullptr)
        return -1;

    // remove the node
    node* root = nullptr;
    int left = 0;

    if((remove_parent->right != nullptr) && (remove_parent->right->data == data))
        root = remove_parent->right;
    else
    {
        root = remove_parent->left;
        left = 1;
    }
    
    node* right = root->right;
    node* pairs = nullptr;
    node* temp = root->left;
    
    if(temp == nullptr)
    {
        if(left)
            remove_parent->left = root->right;
        else
            remove_parent->right = root->right;
        free(root);
        this->size_--;
        return 1;
    }

    // find new root
    node* new_root = nullptr;

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

    if(left)
        remove_parent->left = new_root;
    else
        remove_parent->right = new_root;

    new_root->right = right;
    free(root);
    this->size_--;
    return 1;
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

void pairingHeap::inorder_wrap()
{
    this->inorder(this->root_);
}

void pairingHeap::inorder(node* root)
{
    if(root != nullptr)
    {
        inorder(root->left);
        cout << root->data << " ";
        inorder(root->right);
    }
}

pairingHeap::node* pairingHeap::clone(node* root)
{
    if(root == nullptr)
        return nullptr;

    node* clone_root = (node*)malloc(sizeof(node));
    clone_root->data = root->data;
    clone_root->left = clone(root->left);
    clone_root->right = clone(root->right);
    return clone_root;
}
