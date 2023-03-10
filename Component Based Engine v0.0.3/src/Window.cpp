#include "../include/engine/Window.h"
#include "../include/engine/EngineComponents.h"
#include "../include/game/GameComponents.h"

EntityManager* entityManager;
int fps; 
const float FPSPRINTTIME = 0.5f;
float initTime;

Window::Window(){
    this->title = "Game Engine";
}

Window::~Window(){
    delete entityManager;
    CloseWindow();        // Close window and OpenGL context
}

void Window::run(){
    init();
    loop();
}

void Window::init(){
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, title);
    //SetTargetFPS(FPS);               // Set our game to run at 60 frames-per-second
    entityManager = new EntityManager();
    entityManager->init();

    initTime = GetTime();

    Entity& tilemap(entityManager->addEntity("tileset"));
    tilemap.AddComponent<Transform2D>(0, 0, 1, 0);
    tilemap.AddComponent<TileMap>("../res/images/tileset.png", 32);

    Entity& newEntity(entityManager->addEntity("test"));
    newEntity.AddComponent<Transform2D>(100, 100, 4, 0);
    newEntity.AddComponent<BoxCollider2D>(Vector2{0.f, 0.f}, Vector2{16.f, 16.f});
    newEntity.AddComponent<AnimatedSprite>("../res/images/player_walk.png", 16);
    newEntity.GetComponent<AnimatedSprite>()->addAnimation("walk", {0,1,2,3,4,5,6,7});
    newEntity.GetComponent<AnimatedSprite>()->play("walk");
}

void Window::loop(){
    //game loop
    while(!WindowShouldClose()){
        update();
        draw();
    }
}

void Window::update(){
    float delta = GetFrameTime();
    float currentTime = GetTime();
    
    if (currentTime - initTime >= FPSPRINTTIME){ 
        fps = GetFPS();
        initTime = currentTime;
    }
    entityManager->update(delta);
}

void Window::draw(){
    BeginDrawing();

    ClearBackground(BLACK);
    entityManager->draw();
    DrawText(TextFormat("FPS: %d", fps), 15, 15, 20, GREEN);

    EndDrawing();
}