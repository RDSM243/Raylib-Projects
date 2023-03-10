#ifndef TILEMAP_COMPONENT_H
#define TILEMAP_COMPONENT_H

#include <math.h>
#include <array>
#include "../Tile.h"
#include "../Component.h"
#include "./Transform2D.h"
#include "../CollisionSignal.h"
#include "./BoxCollider2D.h"

class TileMap : public Component{
    public:
        TileMap(const char* filePath, uint32_t tile_size);
        ~TileMap();
        void init() override;
        void draw() override;
        void loadLevel();
        CollisionSignal checkTileMapCollisionWith(BoxCollider2D* entityCollider);
        void setCollisionMask(int maskIndex, bool newVal);
        void setCollisionLayer(int layerIndex, bool newVal);
        bool getCollisionMask(int maskIndex);
        bool getCollisionLayer(int layerIndex);
        std::vector<bool> getActiveLayers();
    private:
        std::array<bool, 16> layers;
        std::array<bool, 16> masks;
        uint32_t tile_size;
        int tilemap[3][10] = {
            {-1, 0, -1, 3, -1, 2, 4, -1, -1},
            {-1, 0, -1, -1, -1, -1, -1, -1, -1},
            {-1, -1, 0, -1, -1, 2, 4, -1, -1},
        };
        std::vector<Tile> tiles;
        std::vector<uint32_t> solid_indexes;
        bool is_solid = false;
        Texture2D texture;
        Transform2D* transform;
};

#endif