#ifndef CONFIG_DOT_H
#define CONFIG_DOT_H

struct Config {
  // Keybindings
  int UP_KEY;
  int DOWN_KEY;
  int LEFT_KEY;
  int RIGHT_KEY;
};

void initConfig();
#endif
