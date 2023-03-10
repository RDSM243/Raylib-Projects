#include "../include/engine/components/Sprite.h"

Sprite::Sprite(const char* filePath){
    texture = LoadTexture(filePath);
}

Sprite::~Sprite(){
    UnloadTexture(texture);
}

void Sprite::init(){
    transform = owner -> GetComponent<Transform2D>();
}

void Sprite::draw(){
    DrawTextureEx(texture, transform->getPos(), transform->getRot(), transform->getScl(), color);
}

Texture2D Sprite::getTexture(){
    return texture;
}

void Sprite::setTexture(const char* filePath){
    UnloadTexture(texture);
    texture = LoadTexture(filePath);
}