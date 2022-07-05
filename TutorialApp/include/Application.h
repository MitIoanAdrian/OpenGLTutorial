//
//  Application.h
//  TutorialApp
//
//  Created by Adrian Mit - (p) on 05.07.2022.
//

#ifndef Application_h
#define Application_h

#include <GLFW/glfw3.h>
#include <iostream>

//file: Application.h
class Application
{
public:
    Application() = default;
    Application& operator = (const Application&) = delete;

public:

    bool initialize(const char* window_name, std::size_t width, std::size_t height);

    void update(const float delta_seconds);
    //^ called from run() function. delta seconds is the ammount of time (in seconds) that passed since the last update() call. First call has 0 as argument.

    void render();
    //^ called from run() function.
    

public:
    void run();
    //^ this functions keeps the application alive until user presses escape


private:
    //add members here:
    GLFWwindow* tutorial_Window;
    
    static void key_callback(GLFWwindow*, int, int, int, int);
};

//file: main.cpp
//int main(int argc, const char ** argv)
//{
//    Application a;
//    if(a.initialize("demo",800,600))
//        return -1;
    
//    a.run();
//    return 0;
//}

//docs:
// https://www.opengl.org/resources/libraries/glut/spec3/spec3.html
// https://ogldev.org/www/tutorial01/tutorial01.html



#endif /* Application_h */
