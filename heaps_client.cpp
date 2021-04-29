#include <bits/stdc++.h>
#include "heaps.h"

int main()
{
    pairingHeap p1;
    p1.insert(6);
    p1.insert(2);

    pairingHeap p2;
    p2.insert(5);
    p2.insert(3); 

    pairingHeap p3;
    p3.insert(8);
    p3.insert(4);
    p3.insert(1);

    vector<int> v = {8,6,2,4,9,5,3,26};
    pairingHeap p;
    p.heapify(v.begin(), v.end());
    p.display();
    // p = p3;
    // p.display();

    // pairingHeap p5;
    // meld(p5,p1,p3);
    // p5.display();
    // p5.inorder_wrap();
    return 0;
}
