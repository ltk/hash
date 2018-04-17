// hash.cpp

#include "hash.h"
#include <iostream>

using namespace std;

hash_table* init_table(unsigned int cap) {
  return NULL; // TODO
}

hash_node* init_node(std::string key, unsigned int hashcode, std::string val) {
  return NULL; // TODO
}

bool set_kvp(hash_table* tbl, string key, string value) {
  return false; // TODO
}

float load(hash_table* tbl) {
  return 0.0; // TODO
}

string get_val(hash_table* tbl, std::string key) {
  return ""; // TODO
}

bool contains(hash_table* tbl, std::string key) {
  return false; // TODO
}

bool remove(hash_table* tbl, std::string key) {
  return false; // TODO
}

void resize(hash_table* tbl, unsigned int new_capacity) {
  // TODO - extra credit
}

// implemented for you - feel free to change this one
void print_table(hash_table* tbl) {
  cout << "Hashtable:" << endl;
  cout << "  capacity: " << tbl->capacity << endl;
  cout << "  size:     " << tbl->size << endl;
  cout << "  occupied: " << tbl->occupied << endl;
  cout << "  load:     " << load(tbl) << endl;
  if (tbl->capacity < 130) {
    for (unsigned int i=0; i < tbl->capacity; i++) {
      cout << "[" << i << "]    ";
      if (tbl->table[i] == NULL) {
        cout << "<empty>" << endl;
      } else if (tbl->table[i]->deleted) {
        cout << "<deleted>" << endl;
      } else {
        cout << "\"" << tbl->table[i]->key << "\" = \"" << tbl->table[i]->value << "\"" << endl;
      }
    }
  } else {
    cout << "    <hashtable too big to print out>" << endl;
  }
}

// implemented for you - don't change this one
unsigned int djb2(string key) {
  unsigned int hash = 5381;
  // Leaving the debugging stuff commented out, in case you want to
  // play. It will output the hash at each incremental step so you can
  // see how it takes shape.
  //
  //  cout << "Hashing string \"" << key << "\"" << endl;
  //  cout << bitset<32>(hash) << " " << hash << endl;
  for (size_t i=0; i < key.length(); i++) {
    char c = key[i]; 
    hash = ((hash << 5) + hash) + c;
    // cout << bitset<32>(hash) << " " << hash << endl;
  }
  // cout << "Hashed string \"" << key << "\" to " << hash << endl;
  //
  // for light reading on why djb2 might not be the best
  // production-grade hash function, go to
  // http://dmytry.blogspot.com/2009/11/horrible-hashes.html
  return hash;
}

// implemented for you - don't change this one
unsigned int modulo_bucket_func(unsigned int hashcode, unsigned int cap) {
  unsigned int b = hashcode % cap;
  return b;
}
