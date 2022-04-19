#include <stdlib.h>

#include "ECS_Table.h"

// Declare helpers
static struct ECS_Table* ecsCreateTableOfSize(size_t sizeIndex);

static const size_t TABLE_SIZES[] = {
  53, 101, 211, 503, 1553, 3407, 6803, 12503, 25013, 50261,
  104729, 250007, 500009, 1000003, 2000029, 4000037, 10000019,
  25000009, 50000047, 104395301, 217645177, 512927357, 1000000007
};

struct ECS_Table* ecsCreateTable() {
  return ecsCreateTableOfSize(0);
}

static struct ECS_Table* ecsCreateTableOfSize(size_t sizeIndex) {
  struct ECS_Table* hashTable;

  hashTable = malloc(sizeof(struct ECS_Table));
  hashTable->size = sizeIndex;
  hashTable->itemCount = 0;

  size_t numElements = TABLE_SIZES[sizeIndex];
  // calloc() to zero-fill pointer array
  hashTable->items = calloc(numElements, sizeof(void *));

  return hashTable;
}

void ecsDestroyTable(struct ECS_Table* hashTable) {
  size_t size = TABLE_SIZES[hashTable->size]; 

  for (size_t i = 0; i < size; i++) {
    struct ECS_Item* item = hashTable->items[i];
    if (item) {
      ecsDestroyItem(item, true);
    }
  }
}

void ecsTableInsert(struct ECS_Table* hashTable, unsigned long key, void* value) {
  size_t size, hash;
  struct ECS_Item* item;

  hash = ecsGenerateHash(hashTable, key);
  item = hashTable->items[hash];

  while (item) {
    // If key previously inserted, replace value with new one.
    if (key == item->key) {
      item->value = value;
      return;
    }
    item = item->next;
  }

  item = ecsCreateItem(key, value);

  item->next = hashTable->items[hash];
  hashTable->items[hash] = item;
  hashTable->itemCount++;

  size = TABLE_SIZES[hashTable->size];
  if (hashTable->itemCount > (size / 2)) {
    size_t newSize = size + 1;
    ecsRehash(hashTable, newSize);
  }

}

void* ecsTableFind(struct ECS_Table* hashTable, unsigned long key) {
  size_t hash;
  struct ECS_Item* item;

  hash = ecsGenerateHash(hashTable, key);
  item = hashTable->items[hash];

  while (item->next) {
    item = item->next;
  }

  if (item) {
    return item;
  }
  else {
    return NULL;
  }

}

void* ecsTableDelete(struct ECS_Table* hashTable, unsigned long key) {
  size_t size, hash;
  struct ECS_Item* item;
  void* value;

  hash = ecsGenerateHash(hashTable, key);
  item = hashTable->items[hash];

  if (key == item->key) {
    hashTable->items[hash] = item->next;
  }
  else {
    while (item) {
      if (item->next && (key == item->next->key)) {
        struct ECS_Item* deletedItem;

        deletedItem = item->next;
        item->next = item->next->next;
        item = deletedItem;
        break;
      }
      item = item->next;
    }
  }

  if (!item) {
    return NULL;
  }


  value = item->value;
  ecsDestroyItem(item, false);
  hashTable->itemCount--;

  size = TABLE_SIZES[hashTable->size];

  if (hashTable->itemCount < size / 8) {
    size_t newSize = size;
    if (size > 0) {
      newSize = size - 1;
    }
    ecsRehash(hashTable, newSize);
  }

  return value;
}


struct ECS_Item* ecsCreateItem(unsigned long key, void* val) {
  struct ECS_Item* item;

  item->key = key;
  item->value = val; 

  return item;

}

void ecsDestroyItem(struct ECS_Item* item, bool recursive) {
  if (recursive && item->next) {
    ecsDestroyItem(item->next, true);
  }
  free(item);
}

size_t ecsGenerateHash(struct ECS_Table* hashTable, unsigned long key) {
  size_t size, hash;

  size = TABLE_SIZES[hashTable->size];
  hash = 0;

  //TODO implement actual hash function.
  hash = key % size;

  return hash;
}

void ecsRehash(struct ECS_Table* hashTable, size_t newSize) {
  size_t hash, size;
  struct ECS_Item** items;

  if (newSize == hashTable->size) {
    return;
  }

  size = TABLE_SIZES[hashTable->size];
  items = hashTable->items;

  hashTable->size = newSize;
  hashTable->items = calloc(TABLE_SIZES[newSize], sizeof(void*));

  for (size_t i = 0; i < size; i++) {
    struct ECS_Item* item;

    item = items[i];
    while (item) {
      struct ECS_Item* nextItem;

      hash = ecsGenerateHash(hashTable, item->key);
      nextItem = item->next;
      item->next = hashTable->items[hash];
      hashTable->items[hash] = item;

      item = nextItem;
    }
  }

  free(items);
}








