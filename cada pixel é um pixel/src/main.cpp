#include "raylib.h"
#include <stdint.h>
#include <iostream>
#include <new>

//To build use 'mingw32-make'
//To run use 'mingw32-make run'
//To build and run use 'mingw32-make build run'

const uint32_t TILESIZE = 4;
uint32_t currentID = 0;

typedef struct particle{
    int pixelID = -1;
    Color color;
} particle;

const Color particle_colors[2] = {YELLOW, BLUE};
const uint32_t screenWidth = 800;
const uint32_t screenHeight = 640;
const int gridWidth = (int)screenWidth/TILESIZE;
const int gridHeight = (int) screenHeight/TILESIZE;
particle** particles;

bool is_inside_grid(int posX, int posY){
    return ((posX < gridWidth && posX > -1) 
    && (posY < gridHeight && posY > -1));
}

bool is_empty(int posX, int posY){
    return (is_inside_grid(posX, posY) && particles[posX][posY].pixelID == -1);
}

void place_particle(int posX, int posY, int pixelID){
    particles[posX][posY].pixelID = pixelID;
    particles[posX][posY].color = particle_colors[pixelID];
}

void clear_particle(int posX, int posY){
    particles[posX][posY].pixelID = -1;
    particles[posX][posY].color = {0};
}

particle* get_particle_at(int posX, int posY){
    return &particles[posX][posY];
}

void update_sand(int posX, int posY){
    bool dir = (GetRandomValue(1,10)%2==0);
    if(posY < screenHeight && particles[posX][posY+1].pixelID == 1){//Checking water and switching Bottom
        place_particle(posX, posY, 1);
        place_particle(posX, posY+1, 0);
    }else if(is_empty(posX, posY+1)){//Bottom
        clear_particle(posX, posY);
        place_particle(posX, posY+1, 0);
    }else if(dir && is_inside_grid(posX+1, posY+1) && particles[posX+1][posY+1].pixelID == 1){//Checking water and switching Bottom Right
        place_particle(posX, posY, 1);
        place_particle(posX+1, posY+1, 0);
    }else if(dir && is_empty(posX+1, posY+1)){//Bottom Right
        clear_particle(posX, posY);
        place_particle(posX+1, posY+1, 0);
    }else if(is_inside_grid(posX-1, posY+1) && particles[posX-1][posY+1].pixelID == 1){//Checking water and switching Bottom Left
        place_particle(posX, posY, 1);
        place_particle(posX-1, posY+1, 0);
    }else if(is_empty(posX-1, posY+1)){//Bottom Left
        clear_particle(posX, posY);
        place_particle(posX-1, posY+1, 0);
    }
}

void update_water(int posX, int posY){
    bool dir = (GetRandomValue(1,10)%2==0);
    if(is_empty(posX, posY+1)){//Bottom
        clear_particle(posX, posY);
        place_particle(posX, posY+1, 1);
    }else if(dir && is_empty(posX+1, posY)){//Right
        clear_particle(posX, posY);
        place_particle(posX+1, posY, 1);
    }else if(is_inside_grid(posX-1, posY) && is_empty(posX-1, posY)){//Left
        clear_particle(posX, posY);
        place_particle(posX-1, posY, 1);
    }
}

void update_particle(int posX, int posY){
    particle* currentParticle = get_particle_at(posX, posY);
    switch(currentParticle->pixelID){
        case 0: //Sand
            update_sand(posX, posY);
        break;
        case 1: //Water
            update_water(posX, posY);
        break;
    }
}
 
int main(int32_t argc, char** argv)
{
    // Initialization
    bool drawGrid = false;

    particles = (particle**) new particle[gridWidth];

    for(int i=0; i < gridWidth; i++){
        particles[i] = (particle*) new particle[gridHeight];
    }

    InitWindow(screenWidth, screenHeight, "Raylib Project");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        
        if(IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)){
            currentID += 1;
            if (currentID >= 2) currentID = 0;
        } 
    
        if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
            Vector2 gridPos = {GetMouseX()/TILESIZE, GetMouseY()/TILESIZE};
            if(is_inside_grid(gridPos.x, gridPos.y)){
                place_particle((int)gridPos.x, (int)gridPos.y, currentID);
            }
        }

        if(IsKeyPressed(KEY_G)){
            drawGrid = !drawGrid;
        }
        
        //----------------------------------------------------------------------------------

        // Draw
        BeginDrawing();

            ClearBackground(BLACK);
            //Drawing particles
            for (int line = 0; line < gridWidth; line++){
                for (int column = 0; column < gridHeight; column++){
                    if(particles[line][column].pixelID > -1){//Verificando se existe particula na posição
                        DrawRectangle((line*TILESIZE), (column*TILESIZE), TILESIZE, TILESIZE, particles[line][column].color);
                        update_particle(line, column);
                    }
                }
            }

            if (drawGrid){
                //Drawing Grid Lines
                for(int i=0; i < gridWidth; i++){
                    DrawLine((int)(i*TILESIZE), 0, (int)(i*TILESIZE), screenHeight, GRAY);
                    DrawLine(0, (int)(i*TILESIZE), screenWidth, (int)(i*TILESIZE), GRAY);
                }
            }

            //Drawing UI
            DrawRectangle(15, 50, TILESIZE*10, TILESIZE*10, particle_colors[currentID]);
            DrawText("Sand", 60, 60, 20, WHITE);
            DrawFPS(15, 20);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    free(particles);
    CloseWindow();     
    //--------------------------------------------------------------------------------------

    return 0;
}