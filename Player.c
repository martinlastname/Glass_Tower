#include "Player.h"

extern unsigned long ENTITIES;
extern struct Component_Tables components;
extern struct Config config;
extern struct Registry drawables, players;

void playerCreate() {
  ENTITIES++;
  unsigned long id = ENTITIES;

  struct Position* positionComponent;
  positionComponent = malloc(sizeof(struct Position));
  positionComponent->id = id;
  positionComponent->position.x = (float)config.screenWidth/2;
  positionComponent->position.y = (float)config.screenHeight/2;
  hashTableInsert(components.position, id, positionComponent);

  struct Player* playerComponent;
  playerComponent = malloc(sizeof(struct Player));
  playerComponent->id = id;
  hashTableInsert(components.player, id, playerComponent);

  struct Drawable_Vector* drawVComponent;
  drawVComponent = malloc(sizeof(struct Drawable_Vector));
  drawVComponent->id = id;
  drawVComponent->visible = true;
  drawVComponent->points = config.playerNumPoints;
  drawVComponent->radius = config.playerRadius;
  drawVComponent->rotation = 0;
  drawVComponent->color = config.playerColor;
  hashTableInsert(components.drawV, id, drawVComponent);

  registerEntity(&drawables, id);
  registerEntity(&players, id);
}

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
