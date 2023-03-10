#include "../include/engine/Entity.h"

Entity::Entity(EntityManager& manager, std::string name): name(name), manager(manager){}

Entity::~Entity(){
    destroy();
}

void Entity::destroy(){
    for(auto& component : components){
        delete component;
    }
}

void Entity::init(){
    for(auto& component : components){
        component->init();
    }
}

void Entity::update(float delta){
    for(auto& component : components){
        component->update(delta);
    }
}

void Entity::draw(){
    for(auto& component : components){
        component->draw();
    }
}

void Entity::listAllComponents() const{
    for(auto& mapElement : componentTypeMap){
        std::cout << "   Component<" << mapElement.first -> name() << ">" << std::endl; 
    }
}

EntityManager& Entity::getManager(){
    return manager;
}