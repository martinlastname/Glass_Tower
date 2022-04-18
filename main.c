#include "raylib.h"

//#include "artist.h"

int ENTITIES = 0;

int screenWidth = 800;
int screenHeight = 450;

struct Position {
  int entityID;
  Vector2 position;
};

struct ComponentLists {
  struct Position position_components[100];
  int totalPositionComponents;
};

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


int main(void)
{

  InitWindow(screenWidth, screenHeight, "raylib [core] example - keyboard input");

  struct ComponentLists components;

  createBall(&components);

  SetTargetFPS(60);

  while (!WindowShouldClose())
  {
    BeginDrawing();

    ClearBackground(RAYWHITE);

    for (int i = 0; i < components.totalPositionComponents; ++i) {
      updatePosition(&components.position_components[i]);
      DrawCircleV(components.position_components[0].position, 50, MAROON);
    }


    EndDrawing();
  }

  CloseWindow();

  return 0;
}
