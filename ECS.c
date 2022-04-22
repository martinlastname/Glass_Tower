#include <stdio.h>

#include "ECS.h"

extern int screenWidth, screenHeight;
extern unsigned long ENTITIES, MIN_KEY;

struct ComponentLists components;

void runSystems() {
  for (int i = MIN_KEY; i <= ENTITIES; ++i) {
    struct Position* p;
    p = ecsTableFind(components.positionComponents, i);
    int a = 0;
    if (p) {
      updatePosition(p);
    }
  }
}

void prepareECS() {
  components.positionComponents = ecsCreateTable();
}

void createBall() {
  ENTITIES++;
  unsigned long id = ENTITIES;

  struct Position* positionComponent;
  positionComponent = malloc(sizeof(struct Position));

  ecsTableInsert(components.positionComponents, id, positionComponent);

  Vector2 ballPosition = { (float)screenWidth/2, (float)screenHeight/2 };
  positionComponent->position = ballPosition;
  positionComponent->entityID = id;
}    

void updatePosition(struct Position* p) {
  char text[20];
  char teyt[20];
  sprintf(text, "%f", p->position.x);
  printf("x: %s\n", text);
  sprintf(teyt, "%f", p->position.y);
  printf("y: %s\n", teyt);

  int x = GetKeyPressed();
  printf("key: %d", x);


  if (IsKeyDown(KEY_RIGHT)) p->position.x += 2.0f;
  if (IsKeyDown(KEY_LEFT)) p->position.x -= 2.0f;
  if (IsKeyDown(KEY_UP)) p->position.y -= 2.0f;
  if (IsKeyDown(KEY_DOWN)) p->position.y += 2.0f;
}
