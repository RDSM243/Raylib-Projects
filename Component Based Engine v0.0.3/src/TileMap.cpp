#include "../include/engine/components/TileMap.h"

TileMap::TileMap(const char* filePath, uint32_t tile_size){
    texture = LoadTexture(filePath);
    this->tile_size = tile_size;
}

TileMap::~TileMap(){
    UnloadTexture(texture);
}

void TileMap::init(){
    loadLevel();
    transform = owner -> GetComponent<Transform2D>();
}

CollisionSignal TileMap::checkTileMapCollisionWith(BoxCollider2D* entityCollider){
    for(auto& tile : tiles){
        if(tile.is_solid){
            if(CheckCollisionRecs(entityCollider->getRectangle(), {tile.pos.x, tile.pos.y, (float)tile_size, (float)tile_size})){
                std::vector<bool> colliderActiveLayers = entityCollider->getActiveLayers();
                for(uint32_t i = 0; i < colliderActiveLayers.size(); i++){
                    if (getCollisionMask(colliderActiveLayers[i])){
                        return {this->owner, colliderActiveLayers[i]};
                    }
                }
            }
        }
    }
    return {};
}

void TileMap::draw(){
    for(auto& tile : tiles){
        uint32_t line_pos = std::floor(tile.tile_index/(texture.width/tile_size));
        uint32_t column_pos = std::abs((int)((line_pos*texture.width) - (tile.tile_index*tile_size)));
        DrawTextureRec(texture, {(float)column_pos, (float)(line_pos * tile_size), (float)tile_size, (float)tile_size}, {tile.pos.x+transform->getPos().x, tile.pos.y+transform->getPos().y}, WHITE);
    }
}

void TileMap::loadLevel(){
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 10; j++){
            if (tilemap[i][j] != -1) {
                tiles.push_back({(uint32_t)tilemap[i][j], {(j*(float)tile_size), (i*(float)tile_size)}, true});
            }
        }
    }
}

void TileMap::setCollisionLayer(int layerIndex, bool newVal){
    layers[layerIndex] = newVal;
}

void TileMap::setCollisionMask(int maskIndex, bool newVal){
    masks[maskIndex] = newVal;
}

bool TileMap::getCollisionLayer(int layerIndex){
    return layers[layerIndex];
}

bool TileMap::getCollisionMask(int maskIndex){
    return masks[maskIndex];
}

std::vector<bool> TileMap::getActiveLayers(){
    std::vector<bool> activeLayers;
    for(uint32_t i = 0; i < layers.size(); i++){
        if (layers[i]) activeLayers.push_back(i);
    }
    return activeLayers;
}