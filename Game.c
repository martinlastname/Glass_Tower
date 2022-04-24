#include "raylib.h"

#include "Game.h"

unsigned long  ENTITIES = 0;
extern unsigned long MIN_KEY;

int screenWidth = 800;
int screenHeight = 450;

extern struct Component_Tables components;

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
  createPlayer();
}

static void drawFrame() {
  BeginDrawing();
  ClearBackground(RAYWHITE);

  // TODO loop over only drawable entities, not all entities
  for (int i = MIN_KEY; i <= ENTITIES; ++i) {
    struct Drawable_Vector* drawable = ecsTableFind(components.drawV, i);
    if (drawable && drawable->visible) {
      struct Position* posC = ecsTableFind(components.position, i);
      switch(drawable->points) {
        case 1:
          DrawCircleV(posC->position, drawable->radius, drawable->color); 
          break;
        case 2:
          break;
        default:
      }
    }
  }

  EndDrawing();
}
