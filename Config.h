#ifndef CONFIG_DOT_H
#define CONFIG_DOT_H

#include "raylib.h"

struct Config {
  int fps;
  int screenWidth;
  int screenHeight;

  // Keybindings
  int UP_KEY;
  int DOWN_KEY;
  int LEFT_KEY;
  int RIGHT_KEY;

  // Player
  int playerNumPoints;
  float playerRadius;
  Color playerColor;

  float playerMoveSpeed;
};

void initConfig();
#endif
