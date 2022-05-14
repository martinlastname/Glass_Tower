#include "raylib.h"

#include "Collision.h"
#include "ECS.h"
#include "Hash_Table.h"

extern struct Component_Tables components;

bool checkPair(unsigned long idA, unsigned long idB) {
	struct Collision* cCollisionA = hashTableFind(components.collision, idA);
	struct Collision* cCollisionB = hashTableFind(components.collision, idB);

	struct Position* cPositionA = hashTableFind(components.position, idA);
	struct Position* cPositionB = hashTableFind(components.position, idB);

  float sizeA, sizeB;
  Vector2 posA, posB;

  if (cPositionA && cPositionB) {
    float sizeA = cCollisionA->size;
    float sizeB = cCollisionB->size;
  }

  if (cCollisionA && cCollisionB) {
    Vector2 posA = cPositionA->position;
    Vector2 posB = cPositionB->position;
  }

	return CheckCollisionCircles(posA, sizeA, posB, sizeB);
}
