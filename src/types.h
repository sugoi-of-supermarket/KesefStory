#ifndef TYPES_H
#define TYPES_H

#include "raylib.h"
#include <stdbool.h>

// Game state enumeration
typedef enum {
    STATE_PLAYING,
    STATE_INVENTORY,
    STATE_PAUSED,
} GameState;

// Entity represents any game object with a sprite
typedef struct {
    Texture2D texture;
    Rectangle source;    // Source rectangle in texture
    Rectangle hitbox;    // Position and size in world
    Vector2   origin;    // Origin point for rotation
    Vector2   velocity;  // Current velocity
} Entity;

// Font collection
typedef struct {
    Font heebo;  // Hebrew-capable font
} Fonts;

// Inventory window state
typedef struct {
    Rectangle dimensions;
    Color     bg_color;
    Color     text_color;
    int       kesef_count;
} InventoryWindow;

#endif // TYPES_H_
