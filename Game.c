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
}

static void initGame() {
  InitWindow(screenWidth, screenHeight, "Glass_Tower");
  SetTargetFPS(60);
  createBall(&components);
}

static void drawFrame() {
  BeginDrawing();

  ClearBackground(RAYWHITE);
  for (int i = 0; i < components.totalPositionComponents; ++i) {
    DrawCircleV(components.position_components[0].position, 50, MAROON);
  }

  EndDrawing();
}
/*
static void runSystems() {
  for (int i = 0; i < components.totalPositionComponents; ++i) {
    updatePosition(&components.position_components[i]);
  }
}*/
