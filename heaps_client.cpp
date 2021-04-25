#include "heaps.h"
using namespace std;

int main()
{
    node* root = make_node(5);
    root = insert(root, 20);
    root = insert(root, 37);
    root = insert(root, 56);
    root = insert(root, 17);
    root = insert(root, 4);
    display(root);
    cout << "\n";
    return 0;
}
