#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <fstream>

using namespace std;


// max_prime is used by the helpful functions provided
// to you.
static const unsigned int max_prime = 1301081;
// the default_capacity is used if the initial capacity 
// of the underlying vector of the hash table is zero. 
static const unsigned int default_capacity = 11;

namespace cop4530{
//--------------Class HashTable-----------------
template <typename K, typename V>//K is the key and V is the value item
class HashTable
{
 public:
   explicit HashTable(size_t size = 101);	//Creates a hash table, the size of the vector is prime_below(size)
   ~HashTable();  

   bool contains(const K & k) const;
   bool match(const std::pair<K,V> &kv);

   bool insert(const std::pair<K,V> & kv);
   bool insert(std::pair<K,V> && kv);
   bool remove(const K &k);
 
   bool load(const char *filename);
   bool write_to_file(const char *filename);
   
   void clear();
   void dump();
   void resize(size_t s);		//helper function to resize

   size_t size();
 
   
  
 private:
   vector<list<std::pair<K,V>>> theList; //the array of lists
   int curSize;
   
   unsigned long prime_below(unsigned long);
   void setPrimes(vector<unsigned long> &);
   void rehash();
   size_t myhash(const K &k) const;
   void makeEmpty();
   
};
#include "hashtable.hpp"
} //end of cop4530
#endif

