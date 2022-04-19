#ifndef GAME_DOT_H
#define GAME_DOT_H

#include "ECS.h"

static struct ComponentLists components;

int runGame();

static void initGame();
static void drawFrame();
static void runSystems();

#endif
