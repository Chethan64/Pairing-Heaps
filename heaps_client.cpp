#include "heaps.h"

int main()
{
    pairingHeap p;
    p.insert(5);
    p.insert(20);
    p.insert(37);
    p.insert(56);
    p.insert(17); 
    p.insert(4);
    // p.display();
    cout << "\n";

    p.extract_minimum();
    // p.display();
    cout << "\n";

    p.extract_minimum();
    // p.insert(200);
    p.extract_minimum();
    p.extract_minimum();
    p.extract_minimum();
    p.extract_minimum();
    p.display();
    cout << "\n";

    return 0;
}
