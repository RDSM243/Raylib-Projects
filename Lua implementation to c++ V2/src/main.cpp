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

class BaseClass{
    public:
        std::string message = "bfdhbfddsfgd";
};

class SubClass : public BaseClass{
    public:
        int num = 2;
};

class SubClass2 : public BaseClass{
    public:
        int num = 5;
};

class TemplateClass{
    public:
        std::vector<BaseClass*> baseClasses; 
        SubClass* subClass = new SubClass();
        TemplateClass(){
            baseClasses.push_back(new BaseClass());
            baseClasses.push_back(new BaseClass());
            baseClasses.push_back(new BaseClass());
        }
        int x;
        void hey(){
            std::cout << "Hello" << std::endl;
        }
        template <typename A, typename B>
        A my_add( A a, B b ) {
                return a + b;
        }
        template <typename T>
        T get_class(T a) {
                std::cout << xurico;
                std::cout<< &typeid(T);
                return a;
        }
        template <typename T>
        std::string return_message(T a, int index) {
                return baseClasses[index]->message;
        }
        template <typename T>
        bool get_classes_message(T a) {
                return a.message;
        }
    private:
        std::string xurico = "oi";
};

int main(void)
{
    lua.open_libraries(sol::lib::base, sol::lib::string);
    
    TemplateClass* test = new TemplateClass();
    TemplateClass* test2 = new TemplateClass();

    test->x = 10;
    test2->x = 30;
    lua.new_usertype<SubClass>("SubClass", "new", sol::no_constructor, "message", &SubClass::message, "number", &SubClass::num);
    lua.new_usertype<TemplateClass>("TemplateClass", "x", &TemplateClass::x, "hey", &TemplateClass::hey, "my_add", sol::overload(&TemplateClass::my_add<int, int>, &TemplateClass::my_add<std::string, std::string>), "sub_class", &TemplateClass::subClass, "get_class", sol::overload(&TemplateClass::get_class<SubClass>, &TemplateClass::get_class<SubClass2>), "get_message", sol::overload(&TemplateClass::return_message<SubClass>, &TemplateClass::return_message<SubClass2>), "get_classes_message", sol::overload(&TemplateClass::get_classes_message<BaseClass>));
    lua["test"] = test;
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
    
    std::string oi = lua["int_num"];

    std::cout << oi;

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