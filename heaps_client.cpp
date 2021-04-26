#include "heaps.h"

int main()
{
    pairingHeap p1;
    p1.insert(6);
    p1.insert(2);
    // p1.display();
    // cout << "\n";

    pairingHeap p2;
    p2.insert(5);
    p2.insert(3); 
    // p2.display();
    // cout << "\n";

    pairingHeap p3;
    p3.insert(8);
    p3.insert(4);
    p3.insert(1);
    // p3.display();
    // cout << "\n";

    pairingHeap p4 = meld(p3, p2);
    p4.display();
    // p3.display();
    // p.extract_minimum();
    // // p.display();
    cout << "\n";
    // p3.merge(p1);
    // p3.display();
    // cout << "\n";
    p4.inorder_wrap();
    cout << "\n\n\n\n";
    pairingHeap p = meld(p4, p1);
    p = p1;
    p.display();
    // p.extract_minimum();
    // p.insert(200);
    // p.insert(12);
    // // p.extract_minimum();
    // // p.extract_minimum();
    // // p.extract_minimum();
    // // p.extract_minimum();
    // p.display();
    cout << "\n";
    p.inorder_wrap();
    cout << "\n";

    return 0;
}
