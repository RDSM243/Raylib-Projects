#ifndef BOX_COLLIDER_2D_COMPONENT_H
#define BOX_COLLIDER_2D_COMPONENT_H

#include <array>
#include "../Component.h"
#include "Transform2D.h"
#include "Sprite.h"
#include "raylib.h"

class BoxCollider2D : public Component{
    public:
        BoxCollider2D();
        BoxCollider2D(Vector2 originPos, Vector2 boxSize);
        ~BoxCollider2D();
        bool isSolid = false;
        bool showCollisionBox = false;
        void init() override;
        void update(float delta) override;
        void draw() override;
        bool CheckCollisionWith(const char* entityName);
        Rectangle getRectangle();
        void setCollisionMask(int maskIndex, bool newVal);
        void setCollisionLayer(int layerIndex, bool newVal);
        bool getCollisionMask(int maskIndex);
        bool getCollisionLayer(int layerIndex);
        std::vector<bool> getActiveLayers();
    private:
        std::array<bool, 16> layers;
        std::array<bool, 16> masks;
        Transform2D* transform;
        Sprite* sprite;
        Rectangle rec;
        Vector2 originPos, boxSize;
};

#endif