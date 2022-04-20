#include "raylib.h"

#include "Game.h"

int ENTITIES = 0;

int screenWidth = 800;
int screenHeight = 450;

extern struct ComponentLists components;

int runGame() {
  initGame();
  while (!WindowShouldClose()) {
    runSystems();
    drawFrame();
  }
  return 0;
}

static void initGame() {
  InitWindow(screenWidth, screenHeight, "Glass_Tower");
  SetTargetFPS(60);
  prepareECS();
  createBall();
}

static void drawFrame() {
  BeginDrawing();

  ClearBackground(RAYWHITE);
  for (int i = 0; i < ENTITIES; ++i) {
    struct Position* drawable = ecsTableFind(components.positionComponents, i);

    if (drawable) {
      DrawCircleV(drawable->position, 50, MAROON);
    }
  }

  EndDrawing();
}
