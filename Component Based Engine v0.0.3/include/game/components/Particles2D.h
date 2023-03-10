#ifndef PARTICLES_2D_COMPONENT_H
#define PARTICLES_2D_COMPONENT_H

#include "../include/engine/Component.h"
#include "../include/engine/EngineComponents.h"
#include "raylib.h"

typedef struct particle2D{
    Vector2 pos;
    Vector2 velocity;
    float lifeTime;
} particle2D;

class Particles2D : public Component{
    public:
        Particles2D();
        Particles2D(bool loop);
        ~Particles2D();
        void clearParticles() const; //Clear all the particles
        void destroyParticle(uint32_t index) const;//Remove Specific particle
        void init() override;
        void update(float delta) override;
        void draw() override;
        bool loop = false;
    private:
        float deltaTime;
        Vector2 originPos;
        Transform2D* transform;
};

#endif