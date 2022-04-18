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
    }
  }
}

void ecsDestroyItem(struct ECS_Item* item) {
  if (item->next) {
    ecsDestroyItem(item->next);
  }
  free(item);
}












