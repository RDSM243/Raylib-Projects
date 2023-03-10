#ifndef TRANSFORM_2D_COMPONENT_H
#define TRANSFORM_2D_COMPONENT_H

#include "raylib.h"
#include "../Component.h"

class Transform2D : public Component{
    public:
        Transform2D(float posX, float posY, float scale, float rotation);
        Transform2D(Vector2 pos, float scale, float rotation);
        Vector2 getPos();
        float getScl();
        float getRot();
        void setPos(Vector2 pos);
        void setPos(float newPosX, float newPosY);
        void setScl(float newScale);
        void setRot(float newRotation);
    private:
        Vector2 pos;
        float scale, rotation;
};

#endif