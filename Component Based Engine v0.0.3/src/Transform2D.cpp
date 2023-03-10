#include "../include/engine/components/Transform2D.h"

Transform2D::Transform2D(float posX, float posY, float scale, float rotation) : pos({posX, posY}), scale(scale), rotation(rotation){}

Transform2D::Transform2D(Vector2 pos, float scale, float rotation) : pos(pos), scale(scale), rotation(rotation){}

Vector2 Transform2D::getPos(){
    return pos;
}

float Transform2D::getScl(){
    return scale;
}

float Transform2D::getRot(){
    return rotation;
}

void Transform2D::setPos(Vector2 newPos){
    this->pos = newPos;
}

void Transform2D::setPos(float newPosX, float newPosY){
    this->pos = {newPosX, newPosY};
}

void Transform2D::setScl(float newScale){
    this->scale = newScale;
}

void Transform2D::setRot(float newRotation){
    this->rotation = newRotation;
}