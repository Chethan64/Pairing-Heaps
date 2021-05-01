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
    private:
        int dd_;
        int mm_;
        int yy_;

    public:
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
    cout << "size : " << p1.size() << "\n";

    pairingHeap<int, more<int>> p2 = p1;
    cout << "\n\n\n" << p2.find_root() << "\n\n\n";
    p2.display();
    cout << "size : " << p2.size() << "\n";

    pairingHeap<int, less<int>> p3;
    create_heap(p3,p1);
    p3.display();
    cout << "size : " << p3.size() << "\n";

    pairingHeap<char, more<char>> p4;
    char arr1[] = {'a','c','b','e'};
    create_heap(p4,arr1,arr1+4);
    p4.display();
    cout << "size : " << p4.size() << "\n";

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
    cout << "size : " << p5.size() << "\n";
    cout << "\n\n";

    pairingHeap<type_a, comp_b> p6;
    create_heap(p6,v1.begin(),v1.end());
    p6.display();
    cout << "size : " << p6.size() << "\n";
    cout << "\n\n";

    type_a arr2[] = {a1,a2,a3,a4};
    pairingHeap<type_a, comp_a> p7;
    create_heap(p7,arr2,arr2+2);
    p7.display();
    cout << "size : " << p7.size() << "\n";
    cout << "\n\n";

    pairingHeap<type_a, comp_a> p8;
    create_heap(p8,arr2+2,arr2+4);
    create_heap(p8,arr2+2,arr2+4);
    insert_heap(p8,p7);
    p8.display();
    cout << "size : " << p8.size() << "\n"; 
    cout << "\n\n";   

    pairingHeap<type_a, comp_a> p9;
    meld(p9,p7,p8);
    p9.display();
    cout << "size : " << p9.size() << "\n";
    cout << "\n\n";

    cout << p9.extract_root() << "\n\n";
    p9.display();
    cout << "size : " << p9.size() << "\n";


    pairingHeap<date, more<date>> p10;
    date d1(29,8,2000);
    date d2(6,4,2000);
    p10.insert(d1);
    p10.insert(d2);
    cout << "size : " << p10.size() << "\n";
    p10.display();

    pairingHeap<date, less<date>> p11;
    create_heap(p11,p10);
    cout << "size : " << p11.size() << "\n";
    p11.display();
    cout << p11.size() << "\n";
    return 0;
}
