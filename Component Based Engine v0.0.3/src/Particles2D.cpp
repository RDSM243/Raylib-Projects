#include "../include/game/components/Particles2D.h"

std::vector<particle2D*> particles;

Particles2D::Particles2D() : originPos({0.f, 0.f}){}

Particles2D::Particles2D(bool loop) : loop(loop), originPos({0.f, 0.f}){}

Particles2D::~Particles2D(){
    clearParticles();
}

void Particles2D::init(){
    transform = owner->GetComponent<Transform2D>();
}

void Particles2D::update(float delta){
    deltaTime = delta;
    if(loop){
        particles.push_back(new (particle2D){{(float)(GetMouseX()), (float)(GetMouseY())},{((float)(GetRandomValue(0, 42)) / 6 - 3.5f)*100, ((float)(GetRandomValue(0, 42)) / 6 - 3.5f)*100}, (float)(GetRandomValue(4, 6))}); 
    }
}

void Particles2D::draw(){
    for(uint32_t i = 0; i < particles.size(); i++){
        particles[i]->pos.x += particles[i]->velocity.x*deltaTime;
        particles[i]->pos.y += particles[i]->velocity.y*deltaTime;
        particles[i]->lifeTime -= 7.5f*deltaTime;
        particles[i]->velocity.y += 15.f*deltaTime;
        DrawCircle(particles[i]->pos.x, particles[i]->pos.y, particles[i]->lifeTime, WHITE);
        //TODO: destroyParticle can't run inside the for loop
        if (particles[i]->lifeTime <= 0){
            destroyParticle(i);
        }
    }
}

void Particles2D::clearParticles() const{
    for(auto& particle : particles){
        free(particle);
    }
    particles.clear();
}

void Particles2D::destroyParticle(uint32_t index) const{
    //deallocating pointer
    free(particles[index]);
    //remove this specific index
    particles.erase(particles.begin()+index);
}