//====================HASHTABLE FUNCTIONS==========================

template <typename K, typename V>
//constructor, creates a hash table where size is set to
//default_capacity
cop4530::HashTable<K,V>::HashTable(size_t s)
{
  theList.resize(prime_below(s));
  curSize = 0;
}

template <typename K, typename V>
//destructor
cop4530::HashTable<K,V>::~HashTable()
{
 makeEmpty();
}

template <typename K, typename V>
//makeEmpty, clears the whole hashtable
void cop4530::HashTable<K,V>::makeEmpty() {
  for( auto & theList : theList)
  { theList.clear(); }
}



template <typename K, typename V>
//resize, resize the table
void cop4530::HashTable<K,V>::resize(size_t s)
{ theList.resize(s); }



template <typename K, typename V>
//clear, clear the table
void cop4530::HashTable<K,V>::clear()
{ makeEmpty(); }



template <typename K, typename V>
//insert, insert using myhash function to insert object
bool cop4530::HashTable<K,V>::insert(const std::pair<K,V> & kv)
{
  auto & whichList = theList[myhash(kv.first)];
  if(match(kv))
   return false;
  
   for(auto itr = whichList.begin(); itr != whichList.end(); ++itr)
   {
     if(itr->first == kv.first)
     {
      auto temp = whichList.erase(itr);
      whichList.insert(temp,kv);
      return true;
     }
   }

   whichList.push_back(kv);
  
  //rehash
  if(++curSize > theList.size())
    rehash();

  return true;
}


template <typename K, typename V>
//Size, return how many entries there are in the table
size_t cop4530::HashTable<K,V>::size()
{ return curSize; }



template <typename K, typename V>
//insert, move version
bool cop4530::HashTable<K,V>::insert(std::pair<K,V> && kv)
{
  const std::pair<K,V> t = std::move(kv);
  insert(t);
  return true;
}


template <typename K, typename V>
//Dump, display all entries in the hash table. If an entry contains multiple key-value pairs
// separate them by a semicolon character (:)
void cop4530::HashTable<K,V>::dump()
{
 for(int i = 0; i < theList.size(); ++i)
 {
   cout << "v[" << i+1 << "]: ";
   for(auto itr = theList[i].begin(); itr != theList[i].end(); ++itr)
   {
     cout << " " << itr->first << " " << itr->second;
 
     if(itr != theList[i].end())
       cout << ":";
   }   
   cout << endl;
 }

}



template <typename K, typename V>
//remove, delete key k and value if in hashtable return true if deleted return false else
bool cop4530::HashTable<K,V>::remove(const K &k)
{
 
 auto & whichList = theList[myhash(k)];
 for(auto itr = whichList.begin(); itr != whichList.end(); ++itr)
 {
    if(itr->first == k)
    {
      whichList.erase(itr);
      --curSize;
      return true;
    }
 }
  
 return false;
}


template <typename K,typename V>
//Myhash, returns the index of the vector entry where k is stored
size_t cop4530::HashTable<K,V>::myhash(const K &k) const
{
  static hash<K> hf;
  return hf(k) % theList.size();
}



template <typename K, typename V>
///Rehash, rehash function if the table get close to full
void cop4530::HashTable<K,V>::rehash()
{
  auto oldList = theList;  
 
  //create new double-sized, empty table
  theList.resize(prime_below(2 * theList.size()));  
  for(auto & thisList : theList)
     thisList.clear();

  //copy table over
  curSize = 0;
  for(auto & thisList: oldList)
  {
   for(auto & x : thisList)
     insert(std::move(x));
  }
}



template <typename K,typename V>
//Contains, checks key k if in hashtable
bool cop4530::HashTable<K,V>::contains(const K &k) const
{
  auto & whichList = theList[myhash(k)];
  for(auto itr = whichList.begin(); itr != whichList.end(); ++itr)
  { 
     if(itr->first == k)
      return true;
  }

  return false;
}



template <typename K, typename V>
//Match, if the 2 pairs inserted match
bool cop4530::HashTable<K,V>::match(const std::pair<K,V> &kv)
{
 auto & whichList = theList[myhash(kv.first)];
 for(auto itr = whichList.begin(); itr != whichList.end(); ++itr)
 {
   if(itr->first == kv.first && itr->second == kv.second)
    return true;
 }
 return false;
}


template <typename K, typename V>
//load, each lie contains a single pair of key and value seperated by whitespace
bool cop4530::HashTable<K,V>::load(const char *filename)
{
  string name,pass;
  std::pair<string,string> np;
  ifstream file(filename);

  if(file.is_open())
  {
    while(file >> name >> pass)
    {
     np.first = name;
     np.second = pass;
     insert(np);
    }
  }    
  else
  {
   cout << "File did not open!" << endl;
   file.close();
   return false;
  }

  file.close();
  return true;
}


template <typename K, typename V>
//write_to_file,
bool cop4530::HashTable<K,V>::write_to_file(const char *filename)
{
 ofstream file(filename);
 for(int i = 0; i < theList.size(); ++i)
 {
   for(auto itr = theList[i].begin(); itr != theList[i].end(); ++itr)
     file << itr->first << " " << itr->second << endl;
 } 

 file.close();
}





//===============Given Functions==================


// returns largest prime number <= n or zero if input is too large
// This is likely to be more efficient than prime_above(), because
// it only needs a vector of size n
template <typename K, typename V>
unsigned long HashTable<K, V>::prime_below (unsigned long n)
{
  if (n > max_prime)
    {
      std::cerr << "** input too large for prime_below()\n";
      return 0;
    }
  if (n == max_prime)
    {
      return max_prime;
    }
  if (n <= 1)
    {
                std::cerr << "** input too small \n";
      return 0;
    }

  // now: 2 <= n < max_prime
  std::vector <unsigned long> v (n+1);
  setPrimes(v);
  while (n > 2)
    {
      if (v[n] == 1)
        return n;
      --n;
    }

  return 2;
}

//Sets all prime number indexes to 1. Called by method prime_below(n)
template <typename K, typename V>
void HashTable<K, V>::setPrimes(std::vector<unsigned long>& vprimes)
{
  int i = 0;
  int j = 0;

  vprimes[0] = 0;
  vprimes[1] = 0;
  int n = vprimes.capacity();

  for (i = 2; i < n; ++i)
    vprimes[i] = 1;

  for( i = 2; i*i < n; ++i)
    {
      if (vprimes[i] == 1)
        for(j = i + i ; j < n; j += i)
          vprimes[j] = 0;
    }
}
