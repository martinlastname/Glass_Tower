#include <stdio.h>

#include "ECS.h"

#include "Player.h"

extern int screenWidth, screenHeight;
extern unsigned long ENTITIES, MIN_KEY;
extern struct Config config;

struct Component_Tables components;
unsigned long* playerArray;

void runSystems() {
  for (size_t i = 0; playerArray[i] != 0; i++) {
    playerMove(playerArray[i]);
  }
}

void prepareECS() {
  playerArray = calloc(64, sizeof(unsigned long));

  components.position = hashCreateTable();
  components.player = hashCreateTable();
  components.drawV = hashCreateTable(); 
}

void registerPlayer(unsigned long id) {
  size_t i = 0;
  while ((i < sizeof(playerArray)) && (playerArray[i] != 0)) {
    i++;
  }
  playerArray[i] = id;
}
