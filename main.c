#include "raylib.h"

#include "ECS.h"

int ENTITIES = 0;

int screenWidth = 800;
int screenHeight = 450;

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
