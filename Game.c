#include <stdio.h>
#include "raylib.h"

#include "Game.h"
#include "Hazard.h"
#include "Player.h"

unsigned long  ENTITIES = 0;
extern unsigned long MIN_KEY;
extern struct Config config;

extern struct Component_Tables components;
extern struct Drawables_List drawables;

int runGame() {
  initGame();
  while (!WindowShouldClose()) {
    runSystems();
    drawFrame();
  }
  return 0;
}

static void initGame() {
  initConfig();
  InitWindow(config.screenWidth, config.screenHeight, "Glass_Tower");
  SetTargetFPS(config.fps);
  prepareECS();
  playerCreate();
  for (int i = 0; i < 5; i++) {
    hazardCreate();
  }
}

static void drawFrame() {
  BeginDrawing();
  ClearBackground(RAYWHITE);

  for (size_t i = 0; i < drawables.count; i++) {
    unsigned long id = drawables.idArray[i];
    struct Drawable_Vector* drawable = hashTableFind(components.drawV, id);
    if (drawable && drawable->visible) {
      struct Position* posC = hashTableFind(components.position, id);
      switch(drawable->points) {
        case 1:
          DrawCircleV(posC->position, drawable->radius, drawable->color); 
          break;
        case 2:
          // TODO rotate line based on drawable->rotation
          Vector2 startPos, endPos;
          startPos.x = posC->position.x - (drawable->radius / 2);
          startPos.y = posC->position.y - (drawable->radius / 2);
          endPos.x = posC->position.x + (drawable->radius / 2);
          endPos.y = posC->position.y + (drawable->radius / 2);
          DrawLineEx(startPos, endPos, drawable->lineThickness, drawable->color);
          break;
        default:
          DrawPoly(posC->position, drawable->points, drawable->radius, drawable->rotation, drawable->color);
      }
    }
  }

  EndDrawing();
}
