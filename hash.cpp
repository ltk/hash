// hash.cpp

#include "hash.h"
#include <iostream>

using namespace std;

hash_table* init_table(unsigned int cap) {
  hash_table* table = new hash_table;
  table->capacity = cap;
  table->size = 0;
  table->occupied = 0;
  table->hash_func = djb2;
  table->bucket_func = modulo_bucket_func;
  table->table = new hash_node*[cap];
  for (int i = 0; i < cap; i++) {
    table->table[i] = NULL;
  }
  return table;
}

hash_node* init_node(std::string key, unsigned int hashcode, std::string val) {
  hash_node* node = new hash_node;
  node->deleted = false;
  node->key = key;
  node->hashcode = hashcode;
  node->value = val;
  return node;
}

bool set_kvp(hash_table* tbl, string key, string value) {
  // If we're at capacity already, it ain't gonna fit.
  cout << "Occupied: " << tbl->occupied << endl;
  if (tbl->capacity == tbl->occupied) {
    return false;
  }

  // Compute hashcode.
  unsigned int hashcode = tbl->hash_func(key);

  hash_node* node = init_node(key, hashcode, value);

  // Find bucket to place in.
  int insert_index = tbl->bucket_func(hashcode, tbl->capacity);

  // Linear Probing
  while(tbl->table[insert_index] && tbl->table[insert_index]->hashcode != hashcode) {
    insert_index = (insert_index + 1) % tbl->capacity;
  }

  insert_index = insert_index % tbl->capacity;

  cout << "adding to index " << insert_index << endl;

  if (!tbl->table[insert_index]) {
    // Increment the table's size + occupied, but only if we added to on empty slot.
    tbl->size++;
    tbl->occupied++;
  }

  // Insert the thing!
  tbl->table[insert_index] = node;

  

  // All is well in the universe.
  return true;
}

float load(hash_table* tbl) {
  return (float)tbl->size / (float)tbl->capacity;
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
