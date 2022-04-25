#ifndef Hash_DATA_DOT_H
#define Hash_DATA_DOT_H
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

struct Hash_Item {
  unsigned long key;
  void* value;
  struct Hash_Item* next;
};

struct Hash_Table {
  size_t size;
  size_t itemCount; 
  struct Hash_Item** items;
};

// Table Operations
struct Hash_Table* hashCreateTable(void);
void hashDestroyTable(struct Hash_Table* hashTable);

void hashTableInsert(struct Hash_Table* hashTable, unsigned long key, void* value);
// Returns null pointer if not found.
void* hashTableFind(struct Hash_Table* hashTable, unsigned long key); 
void* hashTableDelete(struct Hash_Table* hashTable, unsigned long key);

// Item operations
struct Hash_Item* hashCreateItem(unsigned long key, void* val);
void hashDestroyItem(struct Hash_Item* item, bool recursive);

size_t hashGenerateHash(struct Hash_Table* hashTable, unsigned long key);
void hashRehash(struct Hash_Table* hashTable, size_t newSize);


#endif
