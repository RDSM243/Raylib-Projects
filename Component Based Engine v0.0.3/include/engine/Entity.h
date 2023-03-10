#ifndef ENTITY_H
#define ENTITY_H

#include "Component.h"
#include "EntityManager.h"
#include <vector>
#include <map>
#include <string>

class Component;
class EntityManager;

class Entity{
    public:
        Entity(EntityManager& manager, std::string name);
        ~Entity();
        std::string name;
        void destroy();
        void init();
        void update(float delta);
        void draw();
        void listAllComponents() const;
        EntityManager& getManager();
       
        //função para adicionar qualquer tipo de componente
        template<typename T, typename... TArgs>
        T& AddComponent(TArgs&&... args){
            T* newComponent(new T(std::forward<TArgs>(args)...));

            newComponent->owner = this;
            components.emplace_back(newComponent);
            
            //passando o componente para uma lista de componentes
            componentTypeMap[&typeid(*newComponent)] = newComponent;
            
            newComponent->init();

            return *newComponent;
        }

        //Template to verify if the function has a specific component.
        template<typename T>
        bool HasComponent() const{
            return componentTypeMap.count(&typeid(T));
        }

        //Get a specific component from the Entity.
        template<typename T>
        T* GetComponent(){
            //Verifying if the requested component exists
            if (HasComponent<T>()){
                return static_cast<T*>(componentTypeMap[&typeid(T)]);
            }
            std::cerr << "Can't find a component in the entity " << name << std::endl;
            return NULL;
        }
   
    private:
        EntityManager& manager;
        std::vector<Component*> components;
        std::map<const std::type_info*, Component*> componentTypeMap;
};

#endif
