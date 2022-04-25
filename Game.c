#include <stdio.h>
#include "raylib.h"

#include "Game.h"

unsigned long  ENTITIES = 0;
extern unsigned long MIN_KEY;
extern struct Config config;

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
  initConfig();
  InitWindow(screenWidth, screenHeight, "Glass_Tower");
  SetTargetFPS(config.fps);
  prepareECS();
  createPlayer();
}

static void createPlayer() {
  ENTITIES++;
  unsigned long id = ENTITIES;

  struct Position* positionComponent;
  positionComponent = malloc(sizeof(struct Position));
  positionComponent->id = id;
  positionComponent->position.x = (float)screenWidth/2;
  positionComponent->position.y = (float)screenHeight/2;
  hashTableInsert(components.position, id, positionComponent);

  struct Player* playerComponent;
  playerComponent = malloc(sizeof(struct Player));
  playerComponent->id = id;
  hashTableInsert(components.player, id, playerComponent);

  struct Drawable_Vector* drawVComponent;
  drawVComponent = malloc(sizeof(struct Player));
  drawVComponent->id = id;
  drawVComponent->visible = true;
  drawVComponent->points = config.playerNumPoints;
  drawVComponent->radius = config.playerRadius;
  drawVComponent->color = config.playerColor;
  hashTableInsert(components.drawV, id, drawVComponent);

  registerPlayer(id);
}

static void drawFrame() {
  BeginDrawing();
  ClearBackground(RAYWHITE);

  // TODO loop over only drawable entities, not all entities
  for (int i = MIN_KEY; i <= ENTITIES; ++i) {
    struct Drawable_Vector* drawable = hashTableFind(components.drawV, i);
    if (drawable && drawable->visible) {
      struct Position* posC = hashTableFind(components.position, i);
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
