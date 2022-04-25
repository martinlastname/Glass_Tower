#include "Config.h"

struct Config config;

void initConfig() {
  config.fps = 60;

  config.UP_KEY = 87;
  config.DOWN_KEY = 83;
  config.LEFT_KEY = 65;
  config.RIGHT_KEY = 68;

  config.playerNumPoints = 1;
  config.playerRadius = 5.0f;
  config.playerColor = MAROON;

  config.playerMoveSpeed = 2.0f;
}

