#ifndef COLLISION_SIGNAL_H
#define COLLISION_SIGNAL_H

#include "Entity.h"

class Entity;

typedef struct CollisionSignal{
    Entity* otherEntity;//The Entity responsable for the collision
    uint32_t layer; //Layer that collision happens
} CollisionSignal;

#endif