#ifndef WINDOW_H
#define WINDOW_H

#include "raylib.h"
#include "Component.h"
#include "EntityManager.h"

class Window{
    public:
        Window();
        ~Window();
        void run();
        void init();
        void loop();
        void update();
        void draw();
    private:
        const char* title;
        const uint32_t SCREEN_WIDTH = 800;
        const uint32_t SCREEN_HEIGHT = 600;
        const uint32_t FPS = 60;        
};

#endif