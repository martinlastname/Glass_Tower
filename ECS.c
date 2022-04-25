#include <stdio.h>

#include "ECS.h"

#include "Player.h"

extern int screenWidth, screenHeight;
extern unsigned long ENTITIES, MIN_KEY;
extern struct Config config;

struct Component_Tables components;
struct Drawables_List drawables;
unsigned long* playerArray;

void runSystems() {
  for (size_t i = 0; playerArray[i] != 0; i++) {
    playerMove(playerArray[i]);
  }
}

void prepareECS() {
  playerArray = calloc(64, sizeof(unsigned long));
  drawables.idArray = calloc(64, sizeof(unsigned long));
  drawables.count = 0;

  components.position = hashCreateTable();
  components.player = hashCreateTable();
  components.drawV = hashCreateTable(); 
}

void registerPlayer(unsigned long id) {
  size_t i = 0;
  while (playerArray[i] != 0) {
    i++;
  }
  if (i < sizeof(playerArray)) {
    playerArray[i] = id;
  }
}

void registerDrawable(unsigned long id) {
  size_t index = drawables.count;
  if (index == sizeof(drawables.idArray)) {
    unsigned long* oldArray = drawables.idArray;
    size_t newSize = sizeof(oldArray) * 2;
    unsigned long* newArray = calloc(newSize, sizeof(unsigned long));
    for (size_t i = 0; i < sizeof(drawables.idArray); i++) {
      newArray[i] = oldArray[i];
    }
    free(oldArray);
    drawables.idArray = newArray;
  }
  drawables.idArray[index] = id;
  drawables.count++;
}
