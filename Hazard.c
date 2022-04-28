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

  float hSize = 20.0f;
  int  hPoints = 5;

  struct Drawable_Vector* drawVComponent;
  drawVComponent = malloc(sizeof(struct  Drawable_Vector));
  drawVComponent->id = id;
  drawVComponent->visible = true;
  drawVComponent->points = hPoints;
  drawVComponent->radius = hSize;
  drawVComponent->lineThickness = 2;
  drawVComponent->rotation = 180.0f;
  drawVComponent->color = BLUE;
  hashTableInsert(components.drawV, id, drawVComponent);

  // Set collision radius to be as large as possible
  // while entirely within the drawV shape.
  float cSize;
  switch(hPoints) {
    case 1:
    case 2:
      cSize = hSize;
      break;
    case 3:
      cSize = hSize * 0.5f;
      break;
    case 4:
      cSize = hSize * 0.7f;
      break;
    default:
      // TODO improve accuracy for hPoints >= 6
      cSize  = hSize * (1 - (1 / (float)hPoints));
  }
  

  // TODO create tighter colliders for complex shapes.
  struct Collision* collisionComponent;
  collisionComponent = malloc(sizeof(struct Collision));
  collisionComponent->id = id;
  collisionComponent->points = 4;
  collisionComponent->size = cSize;
  hashTableInsert(components.collision, id, collisionComponent);

  registerEntity(&drawables, id);
  registerEntity(&hazards, id);
}
