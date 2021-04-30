#include <bits/stdc++.h>
#include "heaps.h"

template <class T> 
class more {
    public:
        bool operator() (const T& x, const T& y) const {return x>y;}
};

int main()
{
    pairingHeap<int,more<int>> p1;
    p1.insert(61);
    p1.insert(25);
    p1.insert(17);
    p1.insert(8);
    p1.insert(21);
    p1.insert(233);
    p1.insert(456);
    p1.insert(55);
    p1.insert(3);
    p1.insert(37);
    p1.display();
    
    pairingHeap<int,more<int>> p2;
    p2.insert(43);
    p2.insert(54);
    p2.display();

    pairingHeap<int,more<int>> p3;
    meld(p3,p1,p2);
    p3.display();
    // cout << "\n\n" << p1.extract_minimum() << "\n\n\n";
    // p1.display();

    // pairingHeap<int,more<int>>::exhaustive_iterator it;
    // it = p1.get_exhaustive_iterator();
    // cout << *it << "\n";
    // it.next();
    // cout << *it << "\n";
    // it.next();
    // cout << *it << "\n";
    // cout << "\n\n\n";
    // p1.display();
    // cout << "\n\n";
    // p1.inorder_wrap();

    // p1.display();

    // pairingHeap<int,more<int>> p2;
    // p2.insert(5);
    // p2.insert(3); 

    // pairingHeap<char,more<char>> p3;
    // char s1 = 'i';
    // char s2 = 'y';
    // char s3 = 'l';
    // p3.insert(s1);
    // p3.insert(s2);
    // p3.insert(s3);
    // p3.display();

    // vector<int> v = {8,6,2,4,9,5,3,26};
    // pairingHeap<int,more<int>> p;
    // p.heapify(v.begin(), v.end());
    // p.display();
    // p = p3;
    // p.display();

    // pairingHeap p5;
    // meld(p5,p1,p3);
    // p5.display();
    // p5.inorder_wrap();
    return 0;
}
