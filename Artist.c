#include "raylib.h"

#include "ECS.h"

extern struct Component_Tables components;
extern struct Registry drawables, hazards, players;

static RenderTexture2D playerBuf, hazardBuf, debugBuf;

const Color CLEAR = {0, 0, 0, 0};

// Helper methods
static void drawPlayers();
static void drawHazards();
static void drawDebug(struct Position* pos, unsigned long id);
static void drawBuf(RenderTexture2D* buf);

void prepareArtist() {
  int widthBuf = GetScreenWidth();
  int heightBuf = GetScreenHeight();

  playerBuf = LoadRenderTexture(widthBuf, heightBuf);
  hazardBuf = LoadRenderTexture(widthBuf, heightBuf);
  debugBuf = LoadRenderTexture(widthBuf, heightBuf);

}

void drawFrame() {
  BeginTextureMode(hazardBuf);
  ClearBackground(CLEAR);
  drawHazards();
  EndTextureMode();

  BeginTextureMode(playerBuf);
  ClearBackground(CLEAR);
  drawPlayers();
  EndTextureMode();

  BeginDrawing();
  ClearBackground(RAYWHITE);

  drawBuf(&hazardBuf);
  drawBuf(&playerBuf);

  EndDrawing();
}

static void drawBuf(RenderTexture2D* buf) {
  Texture2D texture = buf->texture;
  Rectangle rec = {0, 0, texture.width, -texture.height};
  Vector2 root = {0, 0};
  DrawTextureRec(texture, rec, root, WHITE);
}

static void drawPlayers() {
  for (size_t i = 0; i < players.count; i++) {
    unsigned long id = players.idArray[i];
    struct Position* pos = hashTableFind(components.position, id);
    struct Drawable_Vector* drawable = hashTableFind(components.drawV, id);
    if (drawable && drawable->visible && pos) {
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
    if (drawable && drawable->visible && pos) {
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
