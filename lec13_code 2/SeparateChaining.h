#ifndef SEPARATE_CHAINING_H
#define SEPARATE_CHAINING_H

#include <vector>
#include <list>
#include <string>
#include <algorithm>
#include <functional>
using namespace std;

// SeparateChaining Hash table class
//
// CONSTRUCTION: an approximate initial size or default of 101
//
// ******************PUBLIC OPERATIONS*********************
// bool insert( x )       --> Insert x
// bool remove( x )       --> Remove x
// bool contains( x )     --> Return true if x is present
// void makeEmpty( )      --> Remove all items

template <typename HashedObj>
class HashTable
{
public:
    explicit HashTable(int size = 101);
    bool contains(const HashedObj &x) const;
    void makeEmpty();
    bool insert(const HashedObj &x);
    bool insert(HashedObj &&x);
    bool remove(const HashedObj &x);
    void displayHash();

private:
    vector<list<HashedObj>> theLists; // The array of Lists
    int currentSize;

    void rehash();
    size_t myhash(const HashedObj &x) const;
    size_t hash(const HashedObj &key) const;
    bool isPrime(int n);
    int nextPrime(int n);
};

#endif
