#include "ECS.h"

extern int ENTITIES, screenWidth, screenHeight;

struct ComponentLists components;

void runSystems() {
  for (int i = 0; i < ENTITIES; ++i) {
    updatePosition(ecsTableFind(components.positionComponents, i));
  }
}

void prepareECS() {
  components.positionComponents = ecsCreateTable();
}

void createBall() {
  unsigned long id = (unsigned long)++ENTITIES;

  struct Position* positionComponent;
  positionComponent = malloc(sizeof(struct Position));

  ecsTableInsert(components.positionComponents, id, positionComponent);

  Vector2 ballPosition = { (float)screenWidth/2, (float)screenHeight/2 };
  positionComponent->position = ballPosition;
}    

void updatePosition(struct Position* p) {
  if (IsKeyDown(KEY_RIGHT)) p->position.x += 2.0f;
  if (IsKeyDown(KEY_LEFT)) p->position.x -= 2.0f;
  if (IsKeyDown(KEY_UP)) p->position.y -= 2.0f;
  if (IsKeyDown(KEY_DOWN)) p->position.y += 2.0f;
}
