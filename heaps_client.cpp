#include <bits/stdc++.h>
#include <string>
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
    cout << "\n\n\n\n\n\n" ;
    int b;
    b = p1.remove_element(233);
    b = p1.remove_element(456);
    p1.display();

    pairingHeap<int, more<int>> p2 = p1;
    cout << "\n\n\n" << p2.find_root() << "\n\n\n";
    p2.display();

    return 0;
}
