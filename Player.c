#include "Player.h"

extern struct Component_Tables components;
extern struct Config config;

void playerMove(unsigned long id) {
  struct Position* p = hashTableFind(components.position, id);
  if (IsKeyDown(config.RIGHT_KEY)) {
    p->position.x += config.playerMoveSpeed;
  }
  if (IsKeyDown(config.LEFT_KEY)) {
    p->position.x -= config.playerMoveSpeed;
  }
  if (IsKeyDown(config.UP_KEY)) { 
    p->position.y -= config.playerMoveSpeed;
  }
  if (IsKeyDown(config.DOWN_KEY)) { 
    p->position.y += config.playerMoveSpeed;
  }
}
