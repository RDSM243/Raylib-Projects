#ifndef SPRITE_COMPONENT_H
#define SPRITE_COMPONENT_H

#include "../Component.h"
#include "Transform2D.h"
#include "raylib.h"

class Sprite : public Component{
    public:
        Sprite(const char* filePath);
        ~Sprite();
        void init() override;
        void draw() override;
        Texture2D getTexture();
        void setTexture(const char* filePath);
        Color color = WHITE;
    protected:
        Texture2D texture;
        Transform2D* transform;
};

#endif