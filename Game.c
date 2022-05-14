#include <stdio.h>
#include "raylib.h"

#include "Game.h"

#include "Artist.h"
#include "Hazard.h"
#include "Player.h"

unsigned long  ENTITIES = 0;
extern unsigned long MIN_KEY;
extern struct Config config;

extern struct Component_Tables components;
extern struct Registry drawables;

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
  prepareArtist();
  playerCreate();
  for (int i = 0; i < 1; i++) {
    hazardCreate();
  }
}
