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
  components.player = ecsCreateTable();
  components.drawV = ecsCreateTable(); 
}

void createBall() {
  ENTITIES++;
  unsigned long id = ENTITIES;

  struct Position* positionComponent;
  positionComponent = malloc(sizeof(struct Position));
  positionComponent->id = id;
  positionComponent->position.x = (float)screenWidth/2;
  positionComponent->position.y = (float)screenHeight/2;
  ecsTableInsert(components.position, id, positionComponent);

  struct Player* playerComponent;
  playerComponent = malloc(sizeof(struct Player));
  playerComponent->id = id;
  ecsTableInsert(components.player, id, playerComponent);

  struct Drawable_Vector* drawVComponent;
  drawVComponent = malloc(sizeof(struct Player));
  drawVComponent->id = id;
  drawVComponent->points = 1;
  drawVComponent->radius = 50;
  drawVComponent->color = MAROON;
  ecsTableInsert(components.drawV, id, drawVComponent);

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
