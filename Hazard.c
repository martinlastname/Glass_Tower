#include <stdlib.h>

#include "Hazard.h"

extern unsigned long ENTITIES;
extern struct Component_Tables components;
extern struct Config config;
extern struct Registry drawables, hazards;

void hazardCreate() {
  ENTITIES++;
  unsigned long id = ENTITIES;

  struct Position* positionComponent;
  positionComponent = malloc(sizeof(struct Position));
  positionComponent->id = id;
  positionComponent->position.x = rand() % config.screenWidth;
  positionComponent->position.y = rand() % config.screenHeight;
  hashTableInsert(components.position, id, positionComponent);

  struct Drawable_Vector* drawVComponent;
  drawVComponent = malloc(sizeof(struct  Drawable_Vector));
  drawVComponent->id = id;
  drawVComponent->visible = true;
  drawVComponent->points = 4;
  drawVComponent->radius = 20.0f;
  drawVComponent->lineThickness = 2;
  drawVComponent->rotation = 180.0f;
  drawVComponent->color = BLUE;
  hashTableInsert(components.drawV, id, drawVComponent);

  registerEntity(&drawables, id);
  registerEntity(&hazards, id);
}
