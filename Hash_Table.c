#include "Hash_Table.h"

// Declare helpers
static struct Hash_Table* hashCreateTableOfSize(size_t sizeIndex);

// All keys must be non-zero.
unsigned long MIN_KEY = 1;

static const size_t TABLE_SIZES[] = {
  53, 101, 211, 503, 1553, 3407, 6803, 12503, 25013, 50261,
  104729, 250007, 500009, 1000003, 2000029, 4000037, 10000019,
  25000009, 50000047, 104395301, 217645177, 512927357, 1000000007
};

struct Hash_Table* hashCreateTable() {
  return hashCreateTableOfSize(0);
}

static struct Hash_Table* hashCreateTableOfSize(size_t sizeIndex) {
  struct Hash_Table* hashTable;

  hashTable = malloc(sizeof(struct Hash_Table));
  hashTable->size = sizeIndex;
  hashTable->itemCount = 0;

  size_t numElements = TABLE_SIZES[sizeIndex];
  // calloc() to zero-fill pointer array
  hashTable->items = calloc(numElements, sizeof(void *));

  return hashTable;
}

void hashDestroyTable(struct Hash_Table* hashTable) {
  size_t size = TABLE_SIZES[hashTable->size]; 

  for (size_t i = 0; i < size; i++) {
    struct Hash_Item* item = hashTable->items[i];
    if (item) {
      hashDestroyItem(item, true);
    }
  }
}

void hashTableInsert(struct Hash_Table* hashTable, unsigned long key, void* value) {
  size_t size, hash;
  struct Hash_Item* item;

  hash = hashGenerateHash(hashTable, key);
  item = hashTable->items[hash];

  while (item) {
    // If key previously inserted, replace value with new one.
    if (key == item->key) {
      item->value = value;
      return;
    }
    item = item->next;
  }

  item = hashCreateItem(key, value);

  item->next = hashTable->items[hash];
  hashTable->items[hash] = item;
  hashTable->itemCount++;

  size = TABLE_SIZES[hashTable->size];
  if (hashTable->itemCount > (size / 2)) {
    size_t newSize = size + 1;
    hashRehash(hashTable, newSize);
  }

}

void* hashTableFind(struct Hash_Table* hashTable, unsigned long key) {
  size_t hash;
  struct Hash_Item* item;

  hash = hashGenerateHash(hashTable, key);
  item = hashTable->items[hash];

  while (item) {
    if (item->key != key) {
      item = item->next;
    } else {
      return item->value;
    }
  }

  return NULL;

}

void* hashTableDelete(struct Hash_Table* hashTable, unsigned long key) {
  size_t size, hash;
  struct Hash_Item* item;
  void* value;

  hash = hashGenerateHash(hashTable, key);
  item = hashTable->items[hash];

  if (key == item->key) {
    hashTable->items[hash] = item->next;
  }
  else {
    while (item) {
      if (item->next && (key == item->next->key)) {
        struct Hash_Item* deletedItem;

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
  hashDestroyItem(item, false);
  hashTable->itemCount--;

  size = TABLE_SIZES[hashTable->size];

  if (hashTable->itemCount < size / 8) {
    size_t newSize = size;
    if (size > 0) {
      newSize = size - 1;
    }
    hashRehash(hashTable, newSize);
  }

  return value;
}


struct Hash_Item* hashCreateItem(unsigned long key, void* val) {
  struct Hash_Item* item;

  item = malloc(sizeof(struct Hash_Item));

  item->key = key;
  item->value = val; 

  return item;

}

void hashDestroyItem(struct Hash_Item* item, bool recursive) {
  if (recursive && item->next) {
    hashDestroyItem(item->next, true);
  }
  free(item);
}

size_t hashGenerateHash(struct Hash_Table* hashTable, unsigned long key) {
  size_t size, hash;

  size = TABLE_SIZES[hashTable->size];
  hash = 0;

  //TODO implement actual hash function.
  hash = key % size;
  hash = hash + 1;

  return hash;
}

void hashRehash(struct Hash_Table* hashTable, size_t newSize) {
  size_t hash, size;
  struct Hash_Item** items;

  if (newSize == hashTable->size) {
    return;
  }

  size = TABLE_SIZES[hashTable->size];
  items = hashTable->items;

  hashTable->size = newSize;
  hashTable->items = calloc(TABLE_SIZES[newSize], sizeof(void*));

  for (size_t i = 0; i < size; i++) {
    struct Hash_Item* item;

    item = items[i];
    while (item) {
      struct Hash_Item* nextItem;

      hash = hashGenerateHash(hashTable, item->key);
      nextItem = item->next;
      item->next = hashTable->items[hash];
      hashTable->items[hash] = item;

      item = nextItem;
    }
  }

  free(items);
}








