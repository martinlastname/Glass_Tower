#ifndef ECS_DOT_H
#define ECS_DOT_H

#include <stdbool.h>
#include <stdlib.h>
#include "raylib.h"

#include "Config.h"
#include "Hash_Table.h"

struct Position {
  unsigned long id;
  Vector2 position;
};

struct Player {
  unsigned long id;
  int controller;
};

struct Collision {
  unsigned long id;
  int points;
  float size; // Analogous to radius for simple shapes.
};

// For drawing vectors of regular circles, lines, and regular polygons.
struct Drawable_Vector {
  unsigned long id;
  bool visible;
  int points; // 1 point makes a circle, 2 a line, 3 a triangle, etc.
  float radius;
  float lineThickness;
  float rotation;
  Color color;
};

struct Component_Tables {
  struct Hash_Table* position;
  struct Hash_Table* player;
  struct Hash_Table* drawV;
  struct Hash_Table* collision;
};

struct Registry {
  unsigned long* idArray;
  size_t count;
};

void prepareECS();
void runSystems();

void registerEntity(struct Registry* registry, unsigned long id);
bool registryContainsEntity(struct Registry* registry, unsigned long id);

#endif
