#include <bits/stdc++.h>
#include <iterator>
#include <cstddef>
using namespace std;

/* Template class for pairing-heap
Templatizes the elements of the heap, by default int and the heap comparator by defeault std::less
The pairing heap is represented in left-child - right-sibling format*/
template<typename T=int, typename compare=less<T> >
class pairingHeap {
    private:
        // Structure of the node - stores the data element, left and right node links 
        typedef struct node {
            struct node* left;
            struct node* right;
            T data;
        } node;

        // Private data members
        int size_;
        node* root_;
        node end_;
        compare comparator;
        
        // Private member functions
        node* make_node(const T data) const;
        void display_wrapper(node* root, int indent) const;
        void destroy_heap(node* root);
        node* clone_heap(const node* root) const;
        node* merge_node(node* node1, node* node2) const;
        void find_wrapper(node* parent, node* child, const T data, node** remove_parent) const;
        void inorder(const node* root) const;  
        pairingHeap(node* root):size_(0), root_(root) {}
        
    public:
        // Public member functions
        pairingHeap():size_(0), root_(nullptr) {}
        pairingHeap(const pairingHeap& heap):root_(nullptr)
        {
            this->root_ = this->clone_heap(heap.root_); 
            this->size_ = heap.size_; 
        }
        pairingHeap& operator=(const pairingHeap& pair1);
        ~pairingHeap();
        bool is_empty() const;
        void display() const;
        void insert(const T data);
        T find_root() const;
        T extract_root();
        int remove_element(const T data);
        int size() const;
        void inorder_wrap() const;
        void update_element(const T& data, const T& update);

        // Templatized friend functions
        template<typename T1, typename compare_, typename compare_1>
        friend void insert_heap(pairingHeap<T1, compare_>& pair1, const pairingHeap<T1, compare_1>& pair2);
        
        template<typename T1, typename compare_, typename InputIterator>
        friend void insert_heap(pairingHeap<T, compare>& pair, InputIterator first, InputIterator last);  

        template<typename T1, typename compare_, typename compare_1>
        friend void create_heap(pairingHeap<T1, compare_>& pair1, const pairingHeap<T1, compare_1>& pair2);
        
        template<typename T1, typename compare_, typename InputIterator>
        friend void create_heap(pairingHeap<T, compare>& pair, InputIterator first, InputIterator last);   

        template<typename T1, typename compare_>
        friend void meld(pairingHeap<T1, compare_>& heap, const pairingHeap<T1, compare_>& heap1, const pairingHeap<T1, compare_>& heap2);

        // Exhaustive iterator - nested class
        class exhaustive_iterator {
            private:
                node* p_it_;
                pairingHeap<T, compare>* temp;
            
            public:
                // Public member functions - constructors
                exhaustive_iterator() : p_it_(nullptr), temp(nullptr) {}
                exhaustive_iterator(pairingHeap<T, compare>* temp_, node* p_it) : p_it_(p_it), temp(temp_) {}
                
                // Public member functions
                exhaustive_iterator& next();
               
                T operator*() const
                {
                    if(p_it_ != nullptr)
                        return p_it_->data;
                    else
                        return T();
                }  
        };

        exhaustive_iterator get_exhaustive_iterator()
        {
            return exhaustive_iterator(this, this->root_);
        }

        // Non-exhaustive iterator - nested class
        class iterator {
            private:
                node* p_it_;
                node* flag;
                pairingHeap<T, compare>* temp;
                pairingHeap<T, compare>* ne_heap;
            
            public:

                using iterator_category = std::forward_iterator_tag;
                using difference_type   = std::ptrdiff_t;
                using value_type        = node;
                using pointer           = node*; 
                using reference         = node&;  

                // Constructors
                iterator() : p_it_(nullptr), temp(nullptr) {}

                iterator(pairingHeap<T, compare>* temp_, node* p_it) : p_it_(p_it), temp(temp_), ne_heap(new pairingHeap()) {
                    temp->end_.left = temp->end_.right = nullptr;
                    temp->end_.data = T();
                    flag = nullptr;
                }
                
                // Public member functions
                void stop_iterator();
               
                T operator*() const
                {
                    if(p_it_ != nullptr)
                        return p_it_->data;
                    else
                        return T();
                }

                iterator& operator++();
                iterator operator++(int);

                bool operator==(iterator& it)
                {                    
                    bool equal = (this->p_it_ == it.p_it_);
                    
                    if(flag == this->p_it_)
                    {
                        if((temp->root_ != nullptr) && (ne_heap->root_ == nullptr) && equal)
                            return 1;
                        
                        if(temp->size() == 1)
                            temp->root_->left = nullptr;

                        this->stop_iterator();
                        ne_heap->root_ = nullptr;
                        delete ne_heap;
                        return equal;
                    }
                    flag = this->p_it_;

                    if(equal)
                    {  
                        temp->root_ = nullptr;
                        this->stop_iterator();
                        ne_heap->root_ = nullptr;
                    }
                    
                    return equal;
                }

                bool operator!=(iterator& it)
                {
                    return !(this->operator==(it));
                }
        };

        iterator begin()
        {
            return iterator(this, this->root_);
        }

        iterator end()
        {
            return iterator(this, &this->end_);
        }
};

// Exhaustive Iterator class member functions
/* Function to move the exhaustive iterator to point to the next root element */
template<typename T, typename compare>
typename pairingHeap<T, compare>::exhaustive_iterator& pairingHeap<T, compare>::exhaustive_iterator::next()
{
    T temp_value = temp->extract_root();
    p_it_ = temp->root_;

    return *this;
}

// Non-exhaustive iterator class member functions

/* Pre-increment
Function to move the iterator to point to the next root element, also inserts the 
deleted element into another heap - ne_heap*/
template<typename T, typename compare>
typename pairingHeap<T, compare>::iterator& pairingHeap<T, compare>::iterator::operator++()
{
    T temp_value = temp->extract_root();
    p_it_ = temp->root_;
    ne_heap->insert(temp_value);

    if((p_it_->left == nullptr) && (p_it_->right == nullptr) && (p_it_ != &temp->end_))
        p_it_->left = &temp->end_;

    return *this;
}

/* Function to perform post increment by storing the value pointed to by the iterator before 
performing pre-increment on it */
template<typename T, typename compare>
typename pairingHeap<T, compare>::iterator pairingHeap<T, compare>::iterator::operator++(int post)
{
    iterator temp(*this);
    ++*this;
    return temp;
}

/* Function to explicitly stop the non-exhaustive iterator, merges the ne_heap with current heap
to get back the initial heap */
template<typename T, typename compare>
void pairingHeap<T, compare>::iterator::stop_iterator()
{
    // If there are no elements left in the original heap
    if(temp->is_empty())
    {
        temp->size_ = ne_heap->size_;
        temp->root_ = ne_heap->clone_heap(ne_heap->root_);
        delete ne_heap;
        return;
    }

    if(ne_heap->is_empty())
    {
        delete ne_heap;
        return;
    }

    compare comparator_; 

    // Comparing using the specified comparator function and joining original heap and ne_heap
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
}

// Pairing heap class member functions

/* Function that creates a new pairing heap node and assigns it with the given data */
template<typename T, typename compare>
typename pairingHeap<T,compare>::node* pairingHeap<T, compare>::make_node(const T data_) const
{
    node* temp = (node*)malloc(sizeof(node));
    temp->data = data_;
    temp->left = nullptr;
    temp->right = nullptr;
    return temp;
}

/* Pairing heap destructor 
destroys the allocated heap, updates size of the heap to zero and root to null */
template<typename T, typename compare>
pairingHeap<T, compare>::~pairingHeap()
{
    this->destroy_heap(this->root_);
    this->size_ = 0;
    this->root_ = nullptr;
}

/* Function that deletes every node of the heap recursively */
template<typename T, typename compare>
void pairingHeap<T, compare>::destroy_heap(node* root)
{
    if(root == nullptr)
        return;

    // Delete all its children
    if(root->left != nullptr)
    {
        destroy_heap(root->left);
        root->left = nullptr;
    }

    // Delete all its siblings
    if(root->right != nullptr)
    {
        destroy_heap(root->right);
        root->right = nullptr;
    }
    
    free(root);
}

/* Function to return the root of the heap */
template<typename T, typename compare>
T pairingHeap<T, compare>::find_root() const
{
    return this->root_->data;
}

/* Function to check if the heap is empty */
template<typename T, typename compare>
bool pairingHeap<T, compare>::is_empty() const
{
    return this->root_ == nullptr;
}

/* Function which replaces the given value with another, if that value exists */
template<typename T, typename compare>
void pairingHeap<T, compare>::update_element(const T& data, const T& update)
{
    if(this->remove_element(data) > 0)
        this->insert(update);
}

/* Function for assigning one heap to another */
template<typename T, typename compare>
pairingHeap<T, compare>& pairingHeap<T, compare>::operator=(const pairingHeap<T, compare>& rhs)
{
    if(this != &rhs)
    {
        destroy_heap(this->root_);
        this->root_ = clone_heap(rhs.root_);
        this->size_ = rhs.size_;
    }
    return *this;
}

/* Friend function to meld two given heaps, heap1 and heap2 and assign the new heap to heap */
template<typename T, typename compare>
void meld(pairingHeap<T, compare>& heap, const pairingHeap<T, compare>& heap1, const pairingHeap<T, compare>& heap2)
{
    compare comparator_;
    
    // If the first heap is empty
    if(heap1.is_empty())
    {
        heap.size_ = heap2.size_;
        heap.root_ = heap.clone_heap(heap2.root_);
        return;
    }

    // If the second heap is empty
    if(heap2.is_empty())
    {
        heap.size_ = heap1.size_;
        heap.root_ = heap.clone_heap(heap1.root_);
        return;
    }

    // If neither heaps are empty, compare using comparator function
    if(comparator_(heap1.root_->data,heap2.root_->data))
    {
        pairingHeap<T, compare> heap3(heap1);
        pairingHeap<T, compare> heap4(heap2);
        typename pairingHeap<T, compare>::node* temp = heap3.root_->left;
        heap3.root_->left = heap4.root_;
        heap4.root_->right = temp;
        heap.size_ = heap3.size_ + heap4.size_;
        heap.root_ = heap3.clone_heap(heap3.root_);
        heap4.root_ = nullptr;
    }
    else
    {
        pairingHeap<T, compare> heap3(heap1);
        pairingHeap<T, compare> heap4(heap2);
        typename pairingHeap<T, compare>::node* temp = heap4.root_->left;
        heap4.root_->left = heap3.root_;
        heap3.root_->right = temp;
        heap.size_ = heap4.size_ + heap3.size_;
        heap.root_ = heap4.clone_heap(heap4.root_);
        heap3.root_ = nullptr;
    }
}

/* Function to insert a given element into the heap */
template<typename T, typename compare>
void pairingHeap<T, compare>::insert(const T data)
{
    node* temp = make_node(data);
    this->root_ = merge_node(this->root_, temp);
    this->size_++;
}

/* Function that compares two nodes based on the comparator and merges them accordingly */
template<typename T, typename compare>
typename pairingHeap<T, compare>::node* pairingHeap<T, compare>::merge_node(node* node1, node* node2) const
{
    if(node1 == nullptr)
        return node2;
    
    if(node2 == nullptr)
        return node1;

    // Decouple the nodes
    if(node2 == node1->right)
        node1->right = nullptr;
    else if(node2 == node1->left)
        node1->left = nullptr;
    else if(node1 == node2->right)
        node2->right = nullptr;
    else if(node1 == node2->left)
        node2->left = nullptr;

    // Merge node1 and node2 based on comparator function
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

/* Function which returns the size of the heap, the number of elements in the heap */
template<typename T, typename compare>
int pairingHeap<T, compare>::size() const
{
    return this->size_;
}

/* Function that removes the root, assigns new root based on left-to-right followed by right-to-left merging
and returns the deleted root data */
template<typename T, typename compare>
T pairingHeap<T, compare>::extract_root()
{
    if(this->is_empty())
        return T();

    node* root = this->root_;
    node* pairs = nullptr;
    node* temp = root->left;
    node* new_root = nullptr;

    // If the root is the only element in the heap, it has no child nodes
    if(temp == nullptr)
    {
        T data = root_->data;
        this->root_ = new_root;
        this->size_ = 0;
        free(root);
        return data;
    }        
    
    // If the root has child nodes, next root has to be chosen based on the comparator function
    // Left-to-right pass of pairing
    while((temp != nullptr) && (temp->right != nullptr))
    {
        node* next_pair = temp->right->right;  
        node* temp_node = merge_node(temp,temp->right);
        temp_node->right = pairs;
        pairs = temp_node;
        temp = next_pair;
    }

    // Odd number of nodes
    if(temp != nullptr)
    {
        temp->right = pairs;
        pairs = temp;
    }

    // Right-to-left pass of merging 
    temp = pairs;

    // One merge
    if(temp->right == nullptr)
    {
        new_root = temp;
        temp = nullptr;
    }
    else
    {
        node* temp_node = temp;
        temp = temp->right->right;
        temp_node->right->right = nullptr;
        new_root = merge_node(temp_node,temp_node->right);
    }

    // Merging until there are no nodes left
    while(temp != nullptr)
    {
        node* temp_node = temp->right;
        temp->right = nullptr;
        new_root = merge_node(new_root,temp);
        temp = temp_node;
    }

    // Assigning new root
    T data = root_->data;
    this->root_ = new_root;
    free(root);

    this->size_--;
    return data;
}

/* Recursive function to find the given element and return a pointer to its parent node if found */
template<typename T, typename compare>
void pairingHeap<T, compare>::find_wrapper(node* parent, node* child, const T data, node** remove_parent) const
{
    if(child == nullptr)
        return;
    
    // Element found
    if(child->data == data)
    {
        *remove_parent = parent;
        return;
    }

    if(comparator(child->data, data))
        find_wrapper(child, child->left, data, remove_parent);
    
    find_wrapper(child, child->right, data, remove_parent);    
}    

/* Function to remove a given element if it exists in the heap and return its value, else returns -1 */
template<typename T, typename compare>   
int pairingHeap<T, compare>::remove_element(const T data)
{
    node* remove_parent = nullptr;
    node* parent = nullptr;
    
    // Find pointer to the parent node of the element to be removed
    find_wrapper(parent, this->root_, data, &remove_parent);

    // If the element is the root of the heap, perform extract_root
    if(this->root_->data == data)
    {
        T num = extract_root();
        return 1;
    }

    if(remove_parent == nullptr)
        return -1;

    node* root = nullptr;
    int left = 0;

    // Check if element is the right child of left child of parent
    // Make root point to the element
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
    
    // Element has no children
    // Delete the node and join the parent and the next sibling
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

    // Find new root by merging the children nodes
    node* new_root = nullptr;

    // Left-to-right pass for pairing
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

    temp = pairs;

    // Single node in the heap
    if(temp->right == nullptr)
    {
        new_root = temp;
        temp = nullptr;
    }

    // Merge the first two nodes into new_root
    else
    {
        node* temp_node = temp;
        temp = temp->right->right;
        new_root = merge_node(temp_node,temp_node->right);
    }

    // Right-to-left pass for merging
    while(temp != nullptr)
    {
        new_root = merge_node(new_root,temp);
        temp = temp->right;
    }

    // Merge the new root to the parent node
    if(left)
        remove_parent->left = new_root;
    else
        remove_parent->right = new_root;

    new_root->right = right;
    free(root);
    this->size_--;
    return 1;
}

/* Function to insert elements between the two given iterators to another given heap  */
template<typename T, typename compare, typename InputIterator>
void insert_heap(pairingHeap<T, compare>& pair, InputIterator first, InputIterator last)
{
    while(first != last)
    {
        pair.insert(*first++);
    }
}

/* Function to insert the contents of one heap into another given heap, the two heaps should be of same 
type but can have different compare functions */
template<typename T, typename compare, typename compare_>
void insert_heap(pairingHeap<T, compare>& pair1, const pairingHeap<T, compare_>& pair2)
{
    typename pairingHeap<T, compare_>::node* cloned_heap = pair2.clone_heap(pair2.root_);
    pairingHeap<T, compare_> temp_heap(cloned_heap);
    typename pairingHeap<T, compare_>::exhaustive_iterator it = temp_heap.get_exhaustive_iterator();

    while(temp_heap.root_ != nullptr)
    {
        pair1.insert(*it);
        it.next();
    }
}

/* Function that destroys the existing heap contents and inserts the elements between the two 
given iterators */
template<typename T, typename compare, typename InputIterator>
void create_heap(pairingHeap<T, compare>& pair, InputIterator first, InputIterator last)
{
    pair.~pairingHeap();    
    while(first != last)
    {
        pair.insert(*first++);
    }
}

/* Function that destroys the existing heap contents and inserts the contents of given heap*/
template<typename T, typename compare, typename compare_>
void create_heap(pairingHeap<T, compare>& pair1, const pairingHeap<T, compare_>& pair2)
{
    pair1.~pairingHeap();
    typename pairingHeap<T, compare_>::node* cloned_heap = pair2.clone_heap(pair2.root_);
    pairingHeap<T, compare_> temp_heap(cloned_heap);
    typename pairingHeap<T, compare_>::exhaustive_iterator it = temp_heap.get_exhaustive_iterator();

    while(temp_heap.root_ != nullptr)
    {
        pair1.insert(*it);
        it.next();
    }
}

/* Wrapper function to display the contents of the heap */
template<typename T, typename compare>
void pairingHeap<T, compare>::display_wrapper(node* root, int indent) const
{
    if(root == nullptr)
        return;

    if(indent>0)   
    { 
        printf("%*c",(indent)*8,' ');
        cout << "| " << "\n";
        printf("%*c",(indent)*8,' ');
        cout << "└───── " << root->data << "\n";
    }
    else
    {
        printf("%*c",(indent)*8,' ');
        cout << "    " << root->data << "\n";
    }

    node* temp = root;

    if(temp->left != nullptr)
    {
        temp = temp->left;
        display_wrapper(temp,indent+1);
    }

    temp = root;
    if(temp->right != nullptr)
    {
        temp = temp->right;
        display_wrapper(temp,indent);
    } 
    return;
}

/* Function to display the contents of the pairing heap*/
template<typename T, typename compare>
void pairingHeap<T, compare>::display() const
{
    display_wrapper(this->root_, 0);
    cout << "\n";
}

/* Wrapper function to print the elements of the heap in binary tree form in-order */
template<typename T, typename compare>
void pairingHeap<T, compare>::inorder_wrap() const
{
    this->inorder(this->root_);
}

/* Function to print the contents of the heap in binary tree format in in-order */
template<typename T, typename compare>
void pairingHeap<T, compare>::inorder(const node* root) const
{
    if(root != nullptr)
    {
        inorder(root->left);
        cout << root->data << " ";
        inorder(root->right);
    }
}

/* Function to clone the contents of the heap */
template<typename T, typename compare>
typename pairingHeap<T, compare>::node* pairingHeap<T, compare>::clone_heap(const node* root) const
{
    if(root == nullptr)
        return nullptr;

    node* clone_root = (node*)malloc(sizeof(node));
    clone_root->data = root->data;
    clone_root->left = clone_heap(root->left);
    clone_root->right = clone_heap(root->right);
    return clone_root;
}
