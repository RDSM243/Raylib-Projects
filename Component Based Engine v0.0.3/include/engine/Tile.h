#ifndef TILE_H
#define TILE_H

#include <stdint.h>
#include "raylib.h"

typedef struct Tile{
    uint32_t tile_index;
    Vector2 pos;
    bool is_solid = false;
} Tile;

#endif