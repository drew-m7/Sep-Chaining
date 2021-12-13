#include <iostream>
#include "SeparateChaining.h"
#include "SeparateChaining.cpp"
using namespace std;

// Simple main
int main()
{
    HashTable<int> h(7);

    // int a[] = {15, 11, 27, 8, 12, 13, 5};
    int a[] = {15, 11, 27, 8, 12, 13, 5, 16};
    int n = sizeof(a) / sizeof(a[0]);

    // inserting keys into hash table
    for (int i = 0; i < n; i++)
    {
        h.insert(a[i]);
    }

    // display the Hash table
    cout << "Initial hash table:" << endl;
    h.displayHash();

    // delete 12 from hash table
    h.remove(12);

    cout << "\nUpdated hash table after deleting "
         << "12 from the table:" << endl;
    // display the Hash table
    h.displayHash();

    return 0;
}