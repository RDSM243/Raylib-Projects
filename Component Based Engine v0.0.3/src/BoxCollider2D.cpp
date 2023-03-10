#include "../include/engine/components/BoxCollider2D.h"

BoxCollider2D::BoxCollider2D() : originPos({0.f, 0.f}), boxSize({0.f, 0.f}){}

BoxCollider2D::BoxCollider2D(Vector2 originPos, Vector2 boxSize): originPos(originPos), boxSize(boxSize){}

BoxCollider2D::~BoxCollider2D(){}

void BoxCollider2D::init(){
    transform = owner -> GetComponent<Transform2D>();
    sprite = owner -> GetComponent<Sprite>();
    if (boxSize.x == 0.f && boxSize.y == 0.f){ 
        boxSize = {(float)(sprite->getTexture().width), (float)(sprite->getTexture().height)}; 
    }
}

void BoxCollider2D::update(float delta){
    rec = {(transform->getPos().x + originPos.x), (transform->getPos().y + originPos.y), (boxSize.x*transform->getScl()), (boxSize.y*transform->getScl())};
}

void BoxCollider2D::draw(){
    if(showCollisionBox) DrawRectangleLines(rec.x, rec.y, rec.width, rec.height, RED);
}

bool BoxCollider2D::CheckCollisionWith(const char* entityName){
    Rectangle otherRec = owner->getManager().getEntityByName(entityName)->GetComponent<BoxCollider2D>()->getRectangle();
    return CheckCollisionRecs(rec, otherRec);
}

Rectangle BoxCollider2D::getRectangle(){
    return rec;
}

void BoxCollider2D::setCollisionLayer(int layerIndex, bool newVal){
    layers[layerIndex] = newVal;
}

void BoxCollider2D::setCollisionMask(int maskIndex, bool newVal){
    masks[maskIndex] = newVal;
}

bool BoxCollider2D::getCollisionLayer(int layerIndex){
    return layers[layerIndex];
}

bool BoxCollider2D::getCollisionMask(int maskIndex){
    return masks[maskIndex];
}

std::vector<bool> BoxCollider2D::getActiveLayers(){
    std::vector<bool> activeLayers;
    for(uint32_t i = 0; i < layers.size(); i++){
        if (layers[i]) activeLayers.push_back(i);
    }
    return activeLayers;
}