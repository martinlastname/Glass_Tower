#ifndef ECS_DOT_H
#define ECS_DOT_H


struct Position {
  int entityID;
  Vector2 position;
};

struct ComponentLists {
  struct Position position_components[100];
  int totalPositionComponents;
};

void createBall(struct ComponentLists*);

void updatePosition(struct Position* p);

#endif
