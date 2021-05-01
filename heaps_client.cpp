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

    pairingHeap<int, less<int>> p3;
    create_heap(p3,p1);
    p3.display();

    pairingHeap<char, more<char>> p4;
    char arr1[] = {'a','c','b','e'};
    create_heap(p4,arr1,arr1+4);
    p4.display();

    type_a a1,a2,a3,a4;
    a1.a = 1;   a1.b = 'd';
    a2.a = 2;   a2.b = 'c';
    a3.a = 3;   a3.b = 'b';
    a4.a = 4;   a4.b = 'a';
    vector<type_a> v1{a1,a2,a3,a4};

    pairingHeap<type_a, comp_a> p5;
    p5.display();
    create_heap(p5,v1.begin(),v1.end());
    p5.display();
    cout << "\n\n";

    pairingHeap<type_a, comp_b> p6;
    create_heap(p6,v1.begin(),v1.end());
    p6.display();
    cout << "\n\n";

    type_a arr2[] = {a1,a2,a3,a4};
    pairingHeap<type_a, comp_a> p7;
    create_heap(p7,arr2,arr2+2);
    p7.display();
    cout << "\n\n";

    pairingHeap<type_a, comp_a> p8;
    create_heap(p8,arr2+2,arr2+4);
    p8.display(); 
    cout << "\n\n";   

    pairingHeap<type_a, comp_a> p9;
    meld(p9,p7,p8);
    p9.display();
    cout << "\n\n";

    cout << p9.extract_root() << "\n\n";
    p9.display();

    return 0;
}
