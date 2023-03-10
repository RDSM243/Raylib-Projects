#ifndef ANIMATEDSPRITE_COMPONENT_H
#define ANIMATEDSPRITE_COMPONENT_H

#include <vector>
#include "Sprite.h"

class AnimatedSprite : public Sprite{
    public:
        AnimatedSprite(const char* filePath, uint32_t frame_size);
        void init() override;
        void update(float delta) override;
        void draw() override;
        void addAnimation(std::string animName, std::vector<int> animFrames);
        void removeAnimation(std::string animName);
        void play(std::string animName);
        void pause();
        void stop();
        void resume();
        int findAnimationIndex(std::string animName);
    private:
        bool one_shot = false, is_playing = false, flip_h=false, flip_v=false;
        int current_animation=-1;
        uint32_t frame_size, current_frame=0;
        float initTime, animation_time = 0.075f;
        std::vector<std::vector<int>> animationFrames;
        std::vector<std::string> animationNames;
        Rectangle frameRec;
};

#endif