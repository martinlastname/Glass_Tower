#ifndef ECS_DOT_H
#define ECS_DOT_H

#include <stdbool.h>
#include "raylib.h"

#include "Config.h"
#include "Hash_Table.h"

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
  bool visible;
  int points; // 1 point makes a circle, 2 a line, 3 a triangle, etc.
  float radius;
  Color color;
};

struct Component_Tables {
  struct Hash_Table* position;
  struct Hash_Table* player;
  struct Hash_Table* drawV;
};

void prepareECS();
void runSystems();

void updatePosition(struct Position* p);

#endif
