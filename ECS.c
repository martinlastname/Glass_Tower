#include <stdio.h>

#include "ECS.h"

extern int screenWidth, screenHeight;
extern unsigned long ENTITIES, MIN_KEY;
extern struct Config config;

struct Component_Tables components;

void runSystems() {
  for (int i = MIN_KEY; i <= ENTITIES; ++i) {
    struct Position* p;
    p = hashTableFind(components.position, i);
    if (p) {
      updatePosition(p);
    }
  }
}

void prepareECS() {
  components.position = hashCreateTable();
  components.player = hashCreateTable();
  components.drawV = hashCreateTable(); 
}

void updatePosition(struct Position* p) {
  if (IsKeyDown(config.RIGHT_KEY)) {
    p->position.x += 2.0f;
  }
  if (IsKeyDown(config.LEFT_KEY)) {
    p->position.x -= 2.0f;
  }
  if (IsKeyDown(config.UP_KEY)) { 
    p->position.y -= 2.0f;
  }
  if (IsKeyDown(config.DOWN_KEY)) { 
    p->position.y += 2.0f;
  }
}
