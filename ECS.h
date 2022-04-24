#ifndef ECS_DOT_H
#define ECS_DOT_H

#include "raylib.h"
#include "ECS_Table.h"

struct Position {
  unsigned long id;
  Vector2 position;
};

struct Player {
  unsigned long id;
  // TODO assign input/controller mapping per player
};

// For drawing vectors of regular circles, lines, and regular polygons.
struct Drawable_Vector {
  unsigned long id;
  // 1 point makes a circle, 2 a line, 3 a triangle, etc.
  int points;
  float radius;
  Color color;
};

struct Component_Tables {
  struct ECS_Table* position;
  struct ECS_Table* player;
  struct ECS_Table* drawV;
};

void prepareECS();
void createBall();
void runSystems();

void updatePosition(struct Position* p);

#endif
