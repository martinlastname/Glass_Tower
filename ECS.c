#include <stdio.h>

#include "ECS.h"

#include "Player.h"

extern int screenWidth, screenHeight;
extern unsigned long ENTITIES, MIN_KEY;
extern struct Config config;

struct Component_Tables components;
struct Registry drawables, hazards, players;

void runSystems() {
  for (size_t i = 0; i < players.count; i++) {
    playerMove(players.idArray[i]);
  }
}

void prepareECS() {
  players.idArray = calloc(64, sizeof(unsigned long));
  players.count = 0;
  drawables.idArray = calloc(64, sizeof(unsigned long));
  drawables.count = 0;
  hazards.idArray = calloc(64, sizeof(unsigned long));
  hazards.count = 0;

  components.position = hashCreateTable();
  components.player = hashCreateTable();
  components.drawV = hashCreateTable(); 
  components.collision = hashCreateTable();
}

void registerEntity(struct Registry* registry, unsigned long id) {
  size_t index = registry->count;
  if (index == sizeof(registry->idArray)) {
    unsigned long* oldArray = registry->idArray;
    size_t newSize = sizeof(oldArray) * 2;
    unsigned long* newArray = calloc(newSize, sizeof(unsigned long));
    for (size_t i = 0; i < sizeof(registry->idArray); i++) {
      newArray[i] = oldArray[i];
    }
    free(oldArray);
    registry->idArray = newArray;
  }
  registry->idArray[index] = id;
  registry->count++;
}

bool registryContainsEntity(struct Registry* registry, unsigned long id) {
  for(size_t i = 0; i < sizeof(registry->idArray); i++) {
    if (registry->idArray[i] == id) {
      return true;
    }
  }
  return false;
}
