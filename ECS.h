#ifndef ECS_DOT_H
#define ECS_DOT_H

#include "raylib.h"
#include "ECS_Table.h"

struct Position {
  unsigned long entityID;
  Vector2 position;
};

struct ComponentLists {
  struct ECS_Table* positionComponents;
};

void prepareECS();
void createBall();
void runSystems();

void updatePosition(struct Position* p);

#endif
