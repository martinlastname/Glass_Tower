#include <stdlib.h>

#include "Hazard.h"

extern unsigned long ENTITIES;
extern struct Component_Tables components;
extern struct Config config;

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
  drawVComponent->points = 1;
  drawVComponent->radius = 10.0f;
  drawVComponent->color = BLUE;
  hashTableInsert(components.drawV, id, drawVComponent);

  registerDrawable(id);
}
