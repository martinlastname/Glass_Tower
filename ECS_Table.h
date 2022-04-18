#ifndef ECS_DATA_DOT_H
#define ECS_DATA_DOT_H

struct ECS_Item {
  unsigned long key;
  void* value;
  struct ECS_Item* next;
};

struct ECS_Table {
  size_t size;
  size_t itemCount; 
  struct ECS_Item** items;
};

// Table Operations
struct ECS_Table* ecsCreateTable(void);
void ecsDestroyTable(struct ECS_Table* hashTable);

void ecsTableInsert(struct ECS_Table* hashTable, unsigned long key, void* value);
// Returns null pointer if not found.
void* ecsTableFind(struct ECS_Table* hashTable, unsigned long key); 
void* ecsTableDelete(struct ECS_Table* hashTable, unsigned long key);

// Item operations
struct ECS_Item* ecsCreateEntry(unsigned long key, void* val);
void ecsDestroyItem(struct ECS_Item* item);


unsigned long ecsGenerateHash(unsigned long key);
void ecsRehash(struct ECS_Table* hashTable, size_t newSize);


#endif
