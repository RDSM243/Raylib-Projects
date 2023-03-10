#include "../include/engine/components/AnimatedSprite.h"

float transform_scale;

AnimatedSprite::AnimatedSprite(const char* filePath, uint32_t frame_size) : Sprite(filePath){
    this->frame_size = frame_size;
}

void AnimatedSprite::init(){
    initTime = GetTime();
    frameRec = {0.0f, 0.0f, static_cast<float>(frame_size), static_cast<float>(frame_size)};
    Sprite::init();
}

void AnimatedSprite::update(float delta){
    transform_scale = transform->getScl();
    if (is_playing){
        float currentTime = GetTime();
        
        if (currentTime - initTime >= animation_time){
            if(one_shot) is_playing = false; 
            initTime = currentTime;
            current_frame++;
            if(current_frame >= (animationFrames[current_animation][animationFrames[current_animation].size()-1])+1){ 
                current_frame = animationFrames[current_animation][0];
            }
        }

        frameRec.x = animationFrames[current_animation][current_frame]*(frame_size*transform_scale);
    }
}

void AnimatedSprite::draw(){
    Texture tex = texture;
    tex.width = texture.width*transform_scale;
    tex.height = texture.height*transform_scale;
    DrawTextureRec(tex, {frameRec.x, frameRec.y, (flip_h ? -1 : 1)*(frameRec.width*transform_scale), (flip_v ? -1 : 1)*(frameRec.height*transform_scale)}, transform->getPos(), color);
}

void AnimatedSprite::addAnimation(std::string animName, std::vector<int> animFrames){
    animationNames.push_back(animName);
    animationFrames.push_back(animFrames);
}

void AnimatedSprite::removeAnimation(std::string animName){
    int animIndex = findAnimationIndex(animName);
    if (animIndex == -1){
        std::cerr << animName << " is not an animation." << std::endl;
    }else{
        animationNames.erase(animationNames.begin()+animIndex);
        animationFrames.erase(animationFrames.begin()+animIndex);
    }
}

int AnimatedSprite::findAnimationIndex(std::string animName){
    int animIndex = -1;
    for(uint32_t i = 0; i < animationNames.size(); i++){
        if(animationNames[i] == animName){
            animIndex = i;
            break;
        }
    }
    return animIndex;
}

void AnimatedSprite::play(std::string animName){
    current_frame = 0;
    current_animation = findAnimationIndex(animName);
    is_playing = true;
}

void AnimatedSprite::stop(){
    current_frame = 0;
    current_animation = -1;
    is_playing = false;
}

void AnimatedSprite::resume(){
    is_playing = true;
}

void AnimatedSprite::pause(){
    is_playing = false;
}