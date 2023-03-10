#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include <iostream>
#include <vector>
#include "Entity.h"
#include "CollisionSignal.h"

class Entity;

class EntityManager{
    public:
        ~EntityManager();
        void destroy();
        void init();
        void update(float delta);
        void draw();
        void listAllEntities() const;
        bool hasNoEntities();
        Entity& addEntity(std::string entityName);
        Entity* getEntityByName(std::string entityName) const;
        uint32_t getEntityCount();
        CollisionSignal checkEntityCollisions(Entity* entity) const;
    private:
        std::vector<Entity*> entities;
};

#endif