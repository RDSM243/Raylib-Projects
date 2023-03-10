#define SOL_SAFE_USERTYPE 1
#include "raylib.h"
#include "../lib/lua/sol.hpp"
#include "iostream"

//To build use 'mingw32-make'
//To run use 'mingw32-make run'
//To build and run use 'mingw32-make build run'

sol::state lua;

class ScriptComponent{
    public:
        ScriptComponent(std::string script_path) : script_path(script_path){}
        void init(){
            lua.script_file(script_path);
            initFunc = lua["init"];
            updateFunc = lua["update"];
            initFunc();
        }
        void update(float delta){
            updateFunc(delta);
        }
        std::string script_path;
        sol::function initFunc, updateFunc;
};

class TemplateClass{
    public: 
        TemplateClass(){}
        int x;
        void hey(){
            std::cout << "Hello" << std::endl;
        }
};

template <typename A, typename B>
auto my_add( A a, B b ) {
        return a + b;
}

int main(int argc, char* argv[])
{
    lua.open_libraries(sol::lib::base, sol::lib::string);
    
    TemplateClass* test = new TemplateClass();
    TemplateClass* test2 = new TemplateClass();
    
    test->x = 10;
    test2->x = 30;

    lua["test"] = test;
    lua["my_add"] = my_add<int, int>;

    lua.new_usertype<TemplateClass>("TemplateClass", "x", &TemplateClass::x, "hey", &TemplateClass::hey);

    //lua.set_function("add_func", Add);

    // make usertype metatable
	// lua.new_usertype<player>("player", sol::constructors<player(), player(int), player(int, int)>(), "bullets", &player::bullets, "speed", &player::speed, "boost", &player::boost);
    
    ScriptComponent* othercomponent = new ScriptComponent("../res/scripts/testScript2.lua");
    ScriptComponent* component = new ScriptComponent("../res/scripts/testScript.lua");
    
    // Initialization
    const int screenWidth = 800;
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "Lua Implementation");

    component->init();

    lua["test"] = test2;
    othercomponent->init();
    
    

    //SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update

        
        //component->update(GetFrameTime());
        othercomponent->update(1.f);
        component->update(1.f);
        
        //----------------------------------------------------------------------------------
        
        // Draw
        BeginDrawing();
        
        ClearBackground(BLACK);
        DrawFPS(15, 40);
        
        EndDrawing();
        //----------------------------------------------------------------------------------
    }
    
    // De-Initialization
    free(component);
    free(othercomponent);
    free(test);
    free(test2);
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
    
    return 0;
}