#include "raylib.h"

#include "ECS.h"
#include "ECS_Table.h"

extern int ENTITIES, screenWidth, screenHeight;

void createBall(struct ComponentLists* components) {
  int id = ENTITIES++;
  components->position_components[id].entityID = id;
  Vector2 ballPosition = { (float)screenWidth/2, (float)screenHeight/2 };
  components->position_components[id].position = ballPosition;
  components->totalPositionComponents++;
}    

void updatePosition(struct Position* p) {
  if (IsKeyDown(KEY_RIGHT)) p->position.x += 2.0f;
  if (IsKeyDown(KEY_LEFT)) p->position.x -= 2.0f;
  if (IsKeyDown(KEY_UP)) p->position.y -= 2.0f;
  if (IsKeyDown(KEY_DOWN)) p->position.y += 2.0f;
}
