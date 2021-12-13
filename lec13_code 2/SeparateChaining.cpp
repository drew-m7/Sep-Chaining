#include "SeparateChaining.h"
#include <vector>
#include <list>
#include <string>
#include <algorithm>
#include <functional>
using namespace std;

template <typename HashedObj>
HashTable<HashedObj>::HashTable(int size) : currentSize{0}
{
    theLists.resize(size);
}

template <typename HashedObj>
bool HashTable<HashedObj>::contains(const HashedObj &x) const
{
    auto &whichList = theLists[myhash(x)];
    return find(begin(whichList), end(whichList), x) != end(whichList);
}

template <typename HashedObj>
void HashTable<HashedObj>::makeEmpty()
{
    for (auto &thisList : theLists)
        thisList.clear();
}

template <typename HashedObj>
bool HashTable<HashedObj>::insert(const HashedObj &x)
{
    auto &whichList = theLists[myhash(x)];
    if (find(begin(whichList), end(whichList), x) != end(whichList))
        return false;
    whichList.push_back(x);

    // Rehash; see Section 5.5
    if (++currentSize > theLists.size())
        rehash();

    return true;
}

template <typename HashedObj>
bool HashTable<HashedObj>::insert(HashedObj &&x)
{
    auto &whichList = theLists[myhash(x)];
    if (find(begin(whichList), end(whichList), x) != end(whichList))
        return false;
    whichList.push_back(std::move(x));

    // Rehash; see Section 5.5
    if (++currentSize > theLists.size())
        rehash();

    return true;
}

template <typename HashedObj>
bool HashTable<HashedObj>::remove(const HashedObj &x)
{
    auto &whichList = theLists[myhash(x)];
    auto itr = find(begin(whichList), end(whichList), x);

    if (itr == end(whichList))
        return false;

    whichList.erase(itr);
    --currentSize;
    return true;
}

// function to display hash table
template <typename HashedObj>
void HashTable<HashedObj>::displayHash()
{
    for (int i = 0; i < theLists.size(); i++)
    {
        cout << i;
        for (auto x : theLists[i])
            cout << " --> " << x;
        cout << endl;
    }
}

template <typename HashedObj>
void HashTable<HashedObj>::rehash()
{
    vector<list<HashedObj>> oldLists = theLists;

    // Create new double-sized, empty table
    theLists.resize(nextPrime(2 * theLists.size()));
    for (auto &thisList : theLists)
        thisList.clear();

    // Copy table over
    currentSize = 0;
    for (auto &thisList : oldLists)
        for (auto &x : thisList)
            insert(std::move(x));
}

template <typename HashedObj>
size_t HashTable<HashedObj>::myhash(const HashedObj &x) const
{
    return hash(x) % theLists.size();
}

/**
 * A hash routine for ints.
 */
template <typename HashedObj>
size_t HashTable<HashedObj>::hash(const HashedObj &key) const
{
    return key;
}

/**
 * Internal method to test if a positive number is prime.
 * Not an efficient algorithm.
 */
template <typename HashedObj>
bool HashTable<HashedObj>::isPrime(int n)
{
    if (n == 2 || n == 3)
        return true;

    if (n == 1 || n % 2 == 0)
        return false;

    for (int i = 3; i * i <= n; i += 2)
        if (n % i == 0)
            return false;

    return true;
}

/**
 * Internal method to return a prime number at least as large as n.
 * Assumes n > 0.
 */
template <typename HashedObj>
int HashTable<HashedObj>::nextPrime(int n)
{
    if (n % 2 == 0)
        ++n;

    for (; !isPrime(n); n += 2)
        ;

    return n;
}