#include "raylib.h"
#include <stdlib.h>
#include <stdint.h>
#include <vector>
#include <iostream>

//To build use 'mingw32-make'
//To run use 'mingw32-make run'
//To build and run use 'mingw32-make build run'

typedef struct particle{
    Vector2 pos;
    Vector2 velocity;
    float lifeTime;
} particle;

std::vector<particle*> particles;

const uint32_t screenWidth = 800;
const uint32_t screenHeight = 600;

const float TIME = 0.01f;
float initTime, gravity = 1.f; 
int fps;

void clearParticles(){
    for(auto& particle : particles){
        free(particle);
    }
    particles.clear();
}

void destroyParticle(int index){
    //deallocating pointer
    free(particles[index]);
    //remove this specific index
    particles.erase(particles.begin()+index);
}

int main(void)
{
    // Initialization
    InitWindow(screenWidth, screenHeight, "Raylib Particles");

    //SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------
    
    float delta;

    initTime = GetTime();

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {   delta = GetFrameTime();

        if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
            particles.push_back(new (particle){{(float)(GetMouseX()), (float)(GetMouseY())},{((float)(GetRandomValue(0, 42)) / 6 - 3.5f)*100, ((float)(GetRandomValue(0, 42)) / 6 - 3.5f)*100}, (float)(GetRandomValue(4, 6))}); 
        }
        
        float currentTime = GetTime();

        if (currentTime - initTime >= TIME){
            initTime = currentTime;
            fps = GetFPS();
        }
        
        //----------------------------------------------------------------------------------

        // Draw
        BeginDrawing();
            ClearBackground(BLACK);
            for(uint32_t i = 0; i < particles.size(); i++){
                particles[i]->pos.x += (particles[i]->velocity.x)*delta;
                /*if(CheckCollisionPointRec(particles[i]->pos, rec)){
                    particles[i]->velocity.x = -0.7f * particles[i]->velocity.x;
                    particles[i]->velocity.y *= 0.95f;
                    particles[i]->pos.x += particles[i]->velocity.x * 2;
                }*/
                particles[i]->pos.y += (particles[i]->velocity.y)*delta;
                /*if(CheckCollisionPointRec(particles[i]->pos, rec)){
                    particles[i]->velocity.y = -0.7f * particles[i]->velocity.y;
                    particles[i]->velocity.x *= 0.95f;
                    particles[i]->pos.y += particles[i]->velocity.y * 2;
                }*/
                particles[i]->lifeTime -= 7.5f*delta;
                particles[i]->velocity.y += 15.f*delta;
                DrawCircle(particles[i]->pos.x, particles[i]->pos.y, particles[i]->lifeTime, WHITE);
                if (particles[i]->lifeTime <= 0){
                    destroyParticle(i);
                }
            }
            
            DrawText(TextFormat("FPS: %d",fps), 15, 20, 20, GREEN);
        EndDrawing();
        //----------------------------------------------------------------------------------
        
    }

    // De-Initialization
    clearParticles();
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}