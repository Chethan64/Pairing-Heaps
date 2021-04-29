#include <bits/stdc++.h>
using namespace std;

template<typename T, typename compare=less<T> >
class pairingHeap {
    private:
        typedef struct node {
            T data;
            struct node* left;
            struct node* right;
        } node;

        int size_;
        node* root_;
        compare comparator;
        
        node* make_node(T data) const;
        void display_wrapper(node* root) const;
        void destroy_heap(node* root);
        node* clone_heap(node* root);
        node* merge_node(node* node1, node* node2);
        void find_wrapper(node* parent, node* child, T data, node** remove_parent);
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
        void insert(T data);
        T find_min() const;
        void merge(pairingHeap& pair1);
        T extract_minimum();
        T remove_element(T data);
        int size();
        void inorder_wrap();
        void flip_heap(pairingHeap& heap);
        
        template<typename InputIterator>
        void heapify(InputIterator first, InputIterator last);   

        template<typename T1>
        friend void meld(pairingHeap& heap, pairingHeap& heap1, pairingHeap& heap2);

        class iterator {
            private:
                node* p_it_;
                pairingHeap<T, compare>* temp;
                int exhaustive_ = 1;
                pairingHeap<T, compare>* ne_heap;
            
            public:
                iterator() : p_it_(nullptr), temp(nullptr) {}
                iterator(pairingHeap<T, compare>* temp_, node* p_it, int exhaustive) : p_it_(p_it), temp(temp_), exhaustive_(exhaustive) {
                    if(exhaustive_)
                        ne_heap = nullptr;
                    else
                        ne_heap = new pairingHeap();
                }
                
                iterator& next()
                {
                    T temp_value = temp->extract_minimum();
                    p_it_ = temp->root_;

                    if(!exhaustive_)
                        ne_heap->insert(temp_value);

                    cout << "\n\n\nTemp\n";
                    temp->display();
                    cout << "\nNEHEAP\n";
                    ne_heap->display();
                    cout << "\n\n\n";

                    return *this;
                } 
               
                T operator*()
                {
                    return p_it_->data;
                }  

                void stop_iterator()
                {
                    if(!exhaustive_)
                    {
                            if(temp->root_ == nullptr)
                            {
                                temp->size_ = ne_heap->size_;
                                temp->root_ = ne_heap->clone_heap(ne_heap->root_);
                                delete ne_heap;
                                return;
                            }
                            compare comparator_;
                            if(comparator_(temp->root_->data,ne_heap->root_->data))
                            {
                                typename pairingHeap<T, compare>::node* ne_heap_clone = ne_heap->clone_heap(ne_heap->root_);
                                typename pairingHeap<T, compare>::node* temp_node = temp->root_->left;
                                temp->root_->left = ne_heap_clone;
                                ne_heap_clone->right = temp_node;
                                temp->size_ = temp->size_ + ne_heap->size_;
                            }
                            else
                            {
                                typename pairingHeap<T, compare>::node* ne_heap_clone = ne_heap->clone_heap(ne_heap->root_);
                                typename pairingHeap<T, compare>::node* temp_node = ne_heap_clone->left;
                                ne_heap_clone->left = temp->root_;
                                temp->root_->right = temp_node;
                                temp->size_ = temp->size_ + ne_heap->size_;
                                temp->root_ = ne_heap_clone;
                            }
                            delete ne_heap;
                        
                        
                        
                        
                        // meld(*temp,*temp,*ne_heap);
                        // node* ne_heap_root = ne_heap->clone_heap(ne_heap->root_);
                        // node* temp_root = temp->clone_heap(temp->root_);
                        // node* merged_node = temp->merge_node(temp_root, ne_heap_root);
                        // temp->destroy_heap(temp->root_);
                        // temp->root_ = merged_node;
                        // delete ne_heap;
                    }
                }

        };

        iterator get_iterator(int exhaustive = 1)
        {
            return iterator(this, this->root_, exhaustive);
        }
};

template<typename T, typename compare>
typename pairingHeap<T,compare>::node* pairingHeap<T, compare>::make_node(T data) const
{
    node* temp = (node*)malloc(sizeof(node));
    temp->data = data;
    temp->left = nullptr;
    temp->right = nullptr;
    return temp;
}

template<typename T, typename compare>
pairingHeap<T, compare>::~pairingHeap()
{
    this->destroy_heap(this->root_);
    this->root_ = nullptr;
}

template<typename T, typename compare>
void pairingHeap<T, compare>::destroy_heap(node* root)
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

template<typename T, typename compare>
T pairingHeap<T, compare>::find_min() const
{
    return this->root_->data;
}

template<typename T, typename compare>
bool pairingHeap<T, compare>::is_empty() const
{
    return this->root_ == nullptr;
}

template<typename T, typename compare>
pairingHeap<T, compare>& pairingHeap<T, compare>::operator=(pairingHeap<T, compare>& rhs)
{
    if(this != &rhs)
    {
        destroy_heap(this->root_);
        this->root_ = clone_heap(rhs.root_);
        this->size_ = rhs.size_;
    }
    return *this;
}

template<typename T, typename compare>
void meld(pairingHeap<T, compare>& heap, pairingHeap<T, compare>& heap1, pairingHeap<T, compare>& heap2)
{
    if(heap1.root_ == nullptr)
    {
        heap.size_ = heap2.size_;
        heap.root_ = heap.clone_heap(heap2.root_);
        return;
    }

    if(heap2.root_ == nullptr)
    {
        heap.size_ = heap1.size_;
        heap.root_ = heap.clone_heap(heap1.root_);
        return;
    }

    if(comparator(heap1.root_->data,heap2.root_->data))
    {
        pairingHeap<T> heap3(heap1);
        pairingHeap<T> heap4(heap2);
        typename pairingHeap<T, compare>::node* temp = heap3.root_->left;
        heap3.root_->left = heap4.root_;
        heap4.root_->right = temp;
        heap.size_ = heap3.size_ + heap4.size_;
        heap.root_ = heap.clone_heap(heap3.root_);
    }
    else
    {
        pairingHeap<T> heap3(heap1);
        pairingHeap<T> heap4(heap2);
        typename pairingHeap<T, compare>::node* temp = heap4.root_->left;
        heap4.root_->left = heap3.root_;
        heap3.root_->right = temp;
        heap.size_ = heap4.size_ + heap3.size_;
        heap.root_ = heap.clone_heap(heap4.root_);
    }
}

template<typename T, typename compare>
void pairingHeap<T, compare>::insert(T data)
{
    node* temp = make_node(data);
    this->root_ = merge_node(this->root_, temp);
    this->size_++;
}

template<typename T, typename compare>
typename pairingHeap<T, compare>::node* pairingHeap<T, compare>::merge_node(node* node1, node* node2)
{
    if(node1 == nullptr)
        return node2;

    if(comparator(node1->data, node2->data))
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

template<typename T, typename compare>
int pairingHeap<T, compare>::size()
{
    return this->size_;
}

template<typename T, typename compare>
T pairingHeap<T, compare>::extract_minimum()
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
    T data = root_->data;
    free(root);
    this->size_--;
    return data;
}

template<typename T, typename compare>
void pairingHeap<T, compare>::find_wrapper(node* parent, node* child, T data, node** remove_parent)
{
    if(child == nullptr)
        return;
    
    if(child->data == data)
    {
        *remove_parent = parent;
        return;
    }

    if(comparator(child->data, data))
        find_wrapper(child, child->left, data, remove_parent);
    
    find_wrapper(child, child->right, data, remove_parent);    
}    

template<typename T, typename compare>   
T pairingHeap<T, compare>::remove_element(T data)
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

template<typename T, typename compare>
template<typename InputIterator>
void pairingHeap<T, compare>::heapify(InputIterator first, InputIterator last)
{
    while(first != last)
    {
        insert(*first++);
    }
}

template<typename T, typename compare>
void pairingHeap<T, compare>::display_wrapper(node* root) const
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

template<typename T, typename compare>
void pairingHeap<T, compare>::display() const
{
    display_wrapper(this->root_);
    cout << "\n";
}

template<typename T, typename compare>
void pairingHeap<T, compare>::inorder_wrap()
{
    this->inorder(this->root_);
}

template<typename T, typename compare>
void pairingHeap<T, compare>::inorder(node* root)
{
    if(root != nullptr)
    {
        inorder(root->left);
        cout << root->data << " ";
        inorder(root->right);
    }
}

template<typename T, typename compare>
typename pairingHeap<T, compare>::node* pairingHeap<T, compare>::clone_heap(node* root)
{
    if(root == nullptr)
        return nullptr;

    node* clone_root = (node*)malloc(sizeof(node));
    clone_root->data = root->data;
    clone_root->left = clone_heap(root->left);
    clone_root->right = clone_heap(root->right);
    return clone_root;
}
