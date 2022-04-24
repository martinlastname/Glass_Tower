#include <stdio.h>

#include "ECS.h"

extern int screenWidth, screenHeight;
extern unsigned long ENTITIES, MIN_KEY;

struct Component_Tables components;

void runSystems() {
  for (int i = MIN_KEY; i <= ENTITIES; ++i) {
    struct Position* p;
    p = ecsTableFind(components.position, i);
    if (p) {
      updatePosition(p);
    }
  }
}

void prepareECS() {
  components.position = ecsCreateTable();
}

void createBall() {
  ENTITIES++;
  unsigned long id = ENTITIES;

  struct Position* positionComponent;
  positionComponent = calloc(1, sizeof(struct Position));

  ecsTableInsert(components.position, id, positionComponent);

  positionComponent->position.x = (float)screenWidth/2;
  positionComponent->position.y = (float)screenHeight/2;
  positionComponent->id = id;
}    

void updatePosition(struct Position* p) {
  if (IsKeyDown(KEY_RIGHT)) {
    p->position.x += 2.0f;
  }
  if (IsKeyDown(KEY_LEFT)) {
    p->position.x -= 2.0f;
  }
  if (IsKeyDown(KEY_UP)) { 
    p->position.y -= 2.0f;
  }
  if (IsKeyDown(KEY_DOWN)) { 
    p->position.y += 2.0f;
  }
}
