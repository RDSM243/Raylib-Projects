#include "../include/engine/EntityManager.h"
#include "../include/engine/components/BoxCollider2D.h"

EntityManager::~EntityManager(){
    destroy();
}

void EntityManager::destroy(){
    for(auto& entity : entities){
        delete entity;
    }
}

void EntityManager::init(){
    for(auto& entity : entities){
        entity->init();
    }
}

void EntityManager::update(float delta){
    for(auto& entity : entities){
        entity->update(delta);
    }
}

void EntityManager::draw(){
    for(auto& entity : entities){
        entity->draw();
    }
}

void EntityManager::listAllEntities() const{
    uint32_t i = 0;
    for(auto& entity : entities){
        std::cout << "Entity[" << i << "]" << entity -> name << std::endl;
        entity -> listAllComponents();
        i++;
    }
}

bool EntityManager::hasNoEntities(){
    return entities.size() == 0;
}

//Add a entity on the scene in a specific layer.
Entity& EntityManager::addEntity(std::string entityName){
    Entity* entity = new Entity(*this, entityName);
    entities.emplace_back(entity);
    return *entity;
}

Entity* EntityManager::getEntityByName(std::string entityName) const{
    for (auto *entity : entities) {
        if (entity->name.compare(entityName) == 0)
        {
            return entity;
        }
    }
    return NULL;
}

uint32_t EntityManager::getEntityCount(){
    return entities.size();
}

//Check all the collisions of a entity
CollisionSignal EntityManager::checkEntityCollisions(Entity* entity) const{
    if(entity->HasComponent<BoxCollider2D>()){
        BoxCollider2D* collider = entity->GetComponent<BoxCollider2D>();
        for(auto& otherEntity : entities){
            if(otherEntity->name.compare(entity->name) != 0 && otherEntity->HasComponent<BoxCollider2D>()){
                BoxCollider2D* otherCollider = otherEntity->GetComponent<BoxCollider2D>();
                //Verifying collision
                if(CheckCollisionRecs(collider->getRectangle(), otherCollider->getRectangle())){
                    //Verifying collision between layers and masks
                    std::vector<bool> colliderActiveLayers = collider->getActiveLayers();
                    for (uint32_t i = 0; i < colliderActiveLayers.size(); i++){
                        if (otherCollider->getCollisionMask(colliderActiveLayers[i])){
                            return {otherEntity, colliderActiveLayers[i]};
                        }
                    }
                }
            }
        }
    }
    return {};
}
