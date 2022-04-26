#ifndef COLLISION_DOT_H
#define COLLISION_DOT_H

#include <stdbool.h>
#include "raylib.h"

#include "ECS.h"

struct Hit_Shape {
  bool isCircle;
  float radius; // Only used for circles.
  struct Rectangle;
};

// Returns a pointer to an array of shape structs
// which define the hitboxes of a given entity.
void* getBoxes(unsigned long id);

#endif
