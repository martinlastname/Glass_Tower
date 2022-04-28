#include "raylib.h"

#include "ECS.h"

extern struct Component_Tables components;
extern struct Registry drawables, hazards, players;

static RenderTexture2D playerBuf, hazardBuf, debugBuf;

// Helper methods
static void drawPlayers();
static void drawHazards();
static void drawDebug(struct Position* pos, unsigned long id);

void prepareArtist() {
  int widthBuf = GetScreenWidth();
  int heightBuf = GetScreenHeight();

  playerBuf = LoadRenderTexture(widthBuf, heightBuf);
  hazardBuf = LoadRenderTexture(widthBuf, heightBuf);
  debugBuf = LoadRenderTexture(widthBuf, heightBuf);

}

void drawFrame() {
  BeginDrawing();
  ClearBackground(RAYWHITE);

  drawHazards();
  drawPlayers();

  EndDrawing();
}

static void drawPlayers() {
  for (size_t i = 0; i < players.count; i++) {
    unsigned long id = players.idArray[i];
    struct Position* pos = hashTableFind(components.position, id);
    struct Drawable_Vector* drawable = hashTableFind(components.drawV, id);
    if (drawable && pos) {
      switch(drawable->points) {
        case 1:
        case 2:
          DrawCircleV(pos->position, drawable->radius, drawable->color);
          break;
        default:
          DrawPoly(pos->position, drawable->points, drawable->radius, drawable->rotation, drawable->color);
      }
      drawDebug(pos, id);
    }
  }
}

static void drawHazards() {
  for (size_t i = 0; i < hazards.count; i++) {
    unsigned long id = hazards.idArray[i];
    struct Position* pos = hashTableFind(components.position, id);
    struct Drawable_Vector* drawable = hashTableFind(components.drawV, id);
    if (drawable && pos) {
      switch(drawable->points) {
        case 1:
        case 2:
          DrawCircleV(pos->position, drawable->radius, drawable->color);
          break;
        default:
          DrawPoly(pos->position, drawable->points, drawable->radius, drawable->rotation, drawable->color);
      }
      drawDebug(pos, id);
    }
  }
}

static void drawDebug(struct Position* pos, unsigned long id) {
  // Collision outlines
  struct Collision* collider = hashTableFind(components.collision, id);
  if (collider) {
    switch(collider->points) {
      default:
        DrawCircleLines(pos->position.x, pos->position.y,\
            collider->size, ORANGE);
    }
  }
}
