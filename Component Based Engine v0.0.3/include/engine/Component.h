#ifndef COMPONENT_H
#define COMPONENT_H

#include "Entity.h"

class Entity;

class Component {
    public:
        virtual ~Component();
        Entity* owner;
        virtual void init();
        virtual void update(float delta);
        virtual void draw();
};

#endif
