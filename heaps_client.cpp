#include <bits/stdc++.h>
#include <string>
#include "heaps.h"
using namespace std;

template <class T> 
class more {
    public:
        bool operator() (const T& x, const T& y) const {return x>y;}
};

class type_a
{
    public:
        int a;
        char b;

        friend ostream& operator<<(ostream& stream, const struct type_a& item) {
            stream << item.a << " - " << item.b;
            return stream;
        }

};

class comp_a {
    public:
        bool operator() (const type_a& x, const type_a& y) const {return x.a>y.a;}
};

class comp_b {
    public:
        bool operator() (const type_a& x, const type_a& y) const {return x.b>y.b;}
};

class date {
    public:
        int dd_;
        int mm_;
        int yy_;
        date(int dd = 1, int mm = 1, int yy = 1970) : dd_(dd), mm_(mm), yy_(yy) {}
        friend ostream& operator<<(ostream&, const date&);
        friend bool operator<(const date&, const date&);
        friend bool operator>(const date&, const date&);
        friend bool operator==(const date&, const date&);
        friend bool operator!=(const date&, const date&);
};

ostream& operator<<(ostream& o, const date& d)
{
    return o << d.dd_ << "-" << d.mm_ << "-" << d.yy_;
}

bool operator<(const date& date1, const date& date2)
{
    if(date1.yy_ < date2.yy_)
		return true;
	if(date1.yy_ == date2.yy_ && date1.mm_ < date2.mm_)
		return true;
	if(date1.yy_ == date2.yy_ && date1.mm_ == date2.mm_ && date1.dd_ < date2.dd_) 
		return true;
	return false;
}

bool operator>(const date& date1, const date& date2)
{
    if(date1.yy_ > date2.yy_)
		return true;
	if(date1.yy_ == date2.yy_ && date1.mm_ > date2.mm_)
		return true;
	if(date1.yy_ == date2.yy_ && date1.mm_ == date2.mm_ && date1.dd_ > date2.dd_) 
		return true;
	return false;
}

bool operator==(const date& date1, const date& date2) 
{
    return date1.dd_ == date2.dd_ && date1.mm_ == date2.mm_ && date1.yy_ == date2.yy_;
}

bool operator!=(const date& date1, const date& date2)
{
    return !(date1 == date2);
}

int main()
{
    cout << boolalpha;
    
    #if 0

    cout << "\n\n---------------------------------------- INTEGERS ----------------------------------------\n";

    cout << "\n-- Max heap --\n";
    pairingHeap<int,more<int>> p1;
    cout << "\n\nBefore insertion: \n";
    cout << "Empty: " << p1.is_empty() << "\n";
    cout << "Size: " << p1.size() << "\n";
    
    p1.insert(61);
    p1.insert(25);
    p1.insert(8);
    p1.insert(456);
    p1.insert(3);
    p1.insert(37);

    cout << "\nAfter insertion: \n";
    cout << "Empty: " << p1.is_empty() << "\n";
    cout << "Size: " << p1.size() << "\n\n";
    cout << "Displaying: \n\n";
    p1.display();
    cout << "\n\n";

    cout << "Root: " << p1.find_root() << "\n";
    cout << "Size: " << p1.size() << "\n\n";
    cout << "-- Extracting root -- \n\n";
    p1.extract_root();
    
    cout << "Updated heap: \n";
    cout << "Size: " << p1.size() << "\n\n";
    p1.display();
    
    cout << "\n\n-- Creating heap from existing heap --\n";
    pairingHeap<int, less<int>> p2;
    create_heap(p2,p1); 
    cout << "\nDisplaying: \n\n";
    p2.display();
    cout << "\n\n";

    cout << "\n\n-- Creating heap from elements within a pair of iterators --\n";
    pairingHeap<int, more<int>> p3;
    int a1[] = {4, 1, 90};
    for(auto i:a1)
        cout << i << "\t";
    create_heap(p3,a1,a1+3); 
    cout << "\n\nDisplaying: \n\n";
    p3.display();
    cout << "\n";

    cout << "\n\n-- Inserting elements between a pair of iterators to an existing heap --\n";
    vector<int> v1 = {65, 30, 199};
    for(auto i:v1)
        cout << i << "\t";
    insert_heap(p3, v1.begin(), v1.end());
    cout << "\n\nDisplaying: \n";
    cout << "Size: " << p3.size() << "\n\n";
    p3.display();
    cout << "\n";

    cout << "\n\n-- Inserting elements of a heap to an existing heap --\n";
    insert_heap(p3, p1);
    cout << "\n\nDisplaying: \n";
    cout << "Size: " << p3.size() << "\n\n";
    p3.display();
    cout << "\n";

    cout << "\n\n-- Melding two heaps into a new heap --\n";
    pairingHeap<int,more<int>> m1;
    m1.insert(8);
    m1.insert(6);
    m1.insert(12);
    cout << "\n\nDisplaying first heap: \n";
    cout << "Size: " << m1.size() << "\n\n";
    m1.display();
    pairingHeap<int,more<int>> m2;
    m2.insert(4);
    m2.insert(5);
    cout << "\n\nDisplaying second heap: \n";
    cout << "Size: " << m2.size() << "\n\n";
    m2.display();
    pairingHeap<int,more<int>> m3;
    meld(m3,m1,m2);
    cout << "\n\nDisplaying melded heap: \n";
    cout << "Size: " << m3.size() << "\n\n";
    m3.display();

    m3.insert(23);
    m3.insert(37);
    cout << "\n-- Constant forward iterator --\n\n";
    cout << "Iterating through: \n\n";
    m3.display();
    cout << "\n";
    pairingHeap<int,more<int>>::inorder_iterator first = m3.cbegin();
    pairingHeap<int,more<int>>::inorder_iterator last = m3.cend();
    while(first != last)
    {
        cout << *(first++) << "\t";
    }
    cout << "\n\n";

    cout << "-- Using iterators on STL algorithms --\n\n";
    cout << "1. Find: \n";
    int ele = 5;
    pairingHeap<int, more<int>>::inorder_iterator result = find(m3.cbegin(), m3.cend(), ele);
    cout << "Finding element " << ele << "\n";
    if(result != last)
        cout << "Element found\n\n";
    else
        cout << "Element not found\n\n";

    int min_ele = *min_element(m3.cbegin(), m3.cend());
    cout << "2. Minimum element in the heap: " << min_ele << "\n\n";

    int max_ele = *max_element(m3.cbegin(), m3.cend());
    cout << "3. Maximum element in the heap: " << max_ele << "\n\n";

    vector<int> v(m3.size());
    vector<int>::iterator it = v.begin();
    cout << "4. Using copy - copying the elements to vector:\n";
    copy(m3.cbegin(), m3.cend(), it);
    for(auto i:v)
        cout << i << "\t";
    cout << "\n\n";

    cout << "5. find_if - find based on predicate (%10 == 7):\n";
    result = find_if(m3.cbegin(), m3.cend(), [](int i){return i%10 == 7;});
    cout << "  " << *result << "\n";
    #endif

    #if 1
    cout << "\n\n---------------------------------------- DATE ----------------------------------------\n";

    cout << "\n-- Max heap --\n";
    pairingHeap<date,more<date>> p1_d;
    cout << "\n\nBefore insertion: \n";
    cout << "Empty: " << p1_d.is_empty() << "\n";
    cout << "Size: " << p1_d.size() << "\n";
    
    date d1(29, 8, 2000);
    date d2(6, 4, 2000);
    date d3(11, 9, 2001);
    date d4(26, 11, 2001);
    date d5(11, 1, 1966);
    date d6(30, 1, 1948);


    p1_d.insert(d1);
    p1_d.insert(d2);
    p1_d.insert(d3);
    p1_d.insert(d4);
    p1_d.insert(d5);
    p1_d.insert(d6);

    cout << "\nAfter insertion: \n";
    cout << "Empty: " << p1_d.is_empty() << "\n";
    cout << "Size: " << p1_d.size() << "\n\n";
    cout << "Displaying: \n\n";
    p1_d.display();
    cout << "\n\n";

    cout << "Root: " << p1_d.find_root() << "\n";
    cout << "Size: " << p1_d.size() << "\n\n";
    cout << "-- Extracting root -- \n\n";
    p1_d.extract_root();
    
    cout << "Updated heap: \n";
    cout << "Size: " << p1_d.size() << "\n\n";
    p1_d.display();
    
    cout << "\n\n-- Creating heap from existing heap --\n";
    pairingHeap<date, less<date>> p2_d;
    create_heap(p2_d,p1_d); 
    cout << "\nDisplaying: \n\n";
    p2_d.display();
    cout << "\n\n";

    cout << "\n\n-- Creating heap from elements within a pair of iterators --\n";
    pairingHeap<date, more<date>> p3_d;
    date a1[] = {{26, 12, 2004}, {6, 4, 2010}, {29, 8, 2010}};
    for(auto i:a1)
        cout << i << "\t";
    create_heap(p3_d,a1,a1+3); 
    cout << "\n\nDisplaying: \n\n";
    p3_d.display();
    cout << "\n";

    cout << "\n\n-- Inserting elements between a pair of iterators to an existing heap --\n";
    vector<date> v1 = {{2, 4, 2011}, {31, 12, 2020}, {31, 3, 2021}};
    for(auto i:v1)
        cout << i << "\t";
    insert_heap(p3_d, v1.begin(), v1.end());
    cout << "\n\nDisplaying: \n";
    cout << "Size: " << p3_d.size() << "\n\n";
    p3_d.display();
    cout << "\n";

    cout << "\n\n-- Inserting elements of a heap to an existing heap --\n";
    insert_heap(p3_d, p1_d);
    cout << "\n\nDisplaying: \n";
    cout << "Size: " << p3_d.size() << "\n\n";
    p3_d.display();
    cout << "\n";

    cout << "\n\n-- Melding two heaps into a new heap --\n";
    pairingHeap<date,more<date>> m1_d;
    date d7(24, 9, 2019);
    date d8(7, 1, 2020);
    date d9(13, 3, 2020);
    m1_d.insert(d7);
    m1_d.insert(d8);
    m1_d.insert(d9);
    cout << "\n\nDisplaying first heap: \n";
    cout << "Size: " << m1_d.size() << "\n\n";
    m1_d.display();
    pairingHeap<date,more<date>> m2_d;
    date d10(27, 11, 2020);
    date d11(13, 11, 2019);
    m2_d.insert(d10);
    m2_d.insert(d11);
    cout << "\n\nDisplaying second heap: \n";
    cout << "Size: " << m2_d.size() << "\n\n";
    m2_d.display();
    pairingHeap<date,more<date>> m3_d;
    meld(m3_d,m1_d,m2_d);
    cout << "\n\nDisplaying melded heap: \n";
    cout << "Size: " << m3_d.size() << "\n\n";
    m3_d.display();

    date d12(29, 2, 2020);
    date d13(24, 3, 2021);
    m3_d.insert(d12);
    m3_d.insert(d13);
    cout << "\n-- Constant forward iterator --\n\n";
    cout << "Iterating through: \n\n";
    m3_d.display();
    cout << "\n";
    pairingHeap<date,more<date>>::inorder_iterator first = m3_d.cbegin();
    pairingHeap<date,more<date>>::inorder_iterator last = m3_d.cend();
    while(first != last)
    {
        cout << *(first++) << "\t";
    }
    cout << "\n\n";

    cout << "-- Using iterators on STL algorithms --\n\n";
    cout << "1. Find: \n";
    pairingHeap<date, more<date>>::inorder_iterator result = find(m3_d.cbegin(), m3_d.cend(), d11);
    cout << "Finding element " << d11 << "\n";
    if(result != last)
        cout << "Element found\n\n";
    else
        cout << "Element not found\n\n";

    date min_ele = *min_element(m3_d.cbegin(), m3_d.cend());
    cout << "2. Minimum element in the heap: " << min_ele << "\n\n";

    date max_ele = *max_element(m3_d.cbegin(), m3_d.cend());
    cout << "3. Maximum element in the heap: " << max_ele << "\n\n";

    vector<date> v(m3_d.size());
    vector<date>::iterator it = v.begin();
    cout << "4. Using copy - copying the elements to vector:\n";
    copy(m3_d.cbegin(), m3_d.cend(), it);
    for(auto i:v)
        cout << i << "\t";
    cout << "\n\n";

    cout << "5. find_if - find based on predicate (%10 == 7):\n";
    result = find_if(m3_d.cbegin(), m3_d.cend(), [](date i){return i.dd_%10 == 7;});
    cout << "  " << *result << "\n";
    #endif

    return 0;
}
