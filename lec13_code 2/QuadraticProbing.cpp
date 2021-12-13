#include "QuadraticProbing.h"
#include <iostream>
using namespace std;

template <typename HashedObj>
HashTable<HashedObj>::HashTable(int size) : array(nextPrime(size))
{
    makeEmpty();
}

template <typename HashedObj>
void HashTable<HashedObj>::makeEmpty()
{
    currentSize = 0;
    for (auto &entry : array)
        entry.info = EMPTY;
}

template <typename HashedObj>
bool HashTable<HashedObj>::contains(const HashedObj &x) const
{
    return isActive(findPos(x));
}

template <typename HashedObj>
int HashTable<HashedObj>::findPos(const HashedObj &x) const
{
    int offset = 1;
    int currentPos = myhash(x);

    while (array[currentPos].info != EMPTY &&
           array[currentPos].element != x)
    {
        currentPos += offset; // Compute ith probe
        offset += 2;
        if (currentPos >= array.size())
            currentPos -= array.size();
    }

    return currentPos;
}

template <typename HashedObj>
bool HashTable<HashedObj>::isActive(int currentPos) const
{
    return array[currentPos].info == ACTIVE;
}

template <typename HashedObj>
bool HashTable<HashedObj>::insert(const HashedObj &x)
{
    // Insert x as active
    int currentPos = findPos(x);
    if (isActive(currentPos))
        return false;

    if (array[currentPos].info != DELETED)
        ++currentSize;

    array[currentPos].element = x;
    array[currentPos].info = ACTIVE;

    // Rehash; see Section 5.5
    if (currentSize > array.size() / 2)
        rehash();

    return true;
}

template <typename HashedObj>
bool HashTable<HashedObj>::remove(const HashedObj &x)
{
    int currentPos = findPos(x);
    if (!isActive(currentPos))
        return false;

    array[currentPos].info = DELETED;
    return true;
}

template <typename HashedObj>
bool HashTable<HashedObj>::insert(HashedObj &&x)
{
    // Insert x as active
    int currentPos = findPos(x);
    if (isActive(currentPos))
        return false;

    if (array[currentPos].info != DELETED)
        ++currentSize;

    array[currentPos] = std::move(x);
    array[currentPos].info = ACTIVE;

    // Rehash; see Section 5.5
    if (currentSize > array.size() / 2)
        rehash();

    return true;
}

template <typename HashedObj>
void HashTable<HashedObj>::rehash()
{
    vector<HashEntry> oldArray = array;

    // Create new double-sized, empty table
    array.resize(nextPrime(2 * oldArray.size()));
    for (auto &entry : array)
        entry.info = EMPTY;

    // Copy table over
    currentSize = 0;
    for (auto &entry : oldArray)
        if (entry.info == ACTIVE)
            insert(std::move(entry.element));
}

template <typename HashedObj>
size_t HashTable<HashedObj>::myhash(const HashedObj &x) const
{
    return hash(x) % array.size();
}

/*
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

// function to display hash table
template <typename HashedObj>
void HashTable<HashedObj>::displayHash()
{
    for (int i = 0; i < array.size(); i++)
    {
        if (array[i].info == ACTIVE)
            cout << i << " --> " << array[i].element  << endl;
        else
            cout << i << " --> " << "EMPTY"  << endl;
    }
}
