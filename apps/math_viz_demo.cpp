#include <SDL2/SDL.h>
#include <GL/gl.h>

#include <iostream>
#include <numbers> 

#include "perception/math/Random.hpp"
#include "perception/math/Vector2.hpp"
#include "perception/math/Matrix.hpp"

enum class EColors
{
    Green,
    Blue,
    Blue_pastel,
    Red,
    Red_pastel,
    White,
    Black,
    Grey,
    Yellow,
    Light_yellow
};

void Set_draw_color(EColors color)
{
    float r{0}, g{0}, b{0};
    switch(color)
    {
        case EColors::Green:
            r = 0; g = 1; b = 0; 
            break;
        case EColors::Blue:
            r = 0; g = 0; b = 1;
            break;
        case EColors::Blue_pastel:
            r = 109.0f/255.0f; g = 158.0f/255.0f; b = 235.0f/255.0f;
            break;
        case EColors::Red:
            r = 1; g = 0; b = 0;
            break;
        case EColors::Red_pastel:
            r = 234.0f/255.0f; g = 153.0f/255.0f; b = 153.0f/255.0f;
            break;
        case EColors::White:
            r = 1.0; g = 1.0; b = 1.0;
            break;
        case EColors::Black:
            r = 0; g = 0; b = 0;
            break;
        case EColors::Grey:
            r = 153.0f/255.0f; g = 153.0f/255.0f; b = 153.0f/255.0f;
            break;
        case EColors::Yellow:
            r = 255; g = 255; b = 0;
        case EColors::Light_yellow:
            r = 1; g = 229.0f/255.0f; b = 153.0f/255.0f;
            break;
    }
    glColor3f(r, g, b);
}

using namespace perception::math;
int main(int argc, char* argv[])
{   
    // Window height width
    constexpr int WINDOW_WIDTH = 800;
    constexpr int WINDOW_HEIGHT = 800;

    // Initialize graphics display drivers for video backend
    if(SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cerr << "SDL_Init Failed: " << SDL_GetError() << "\n";
        return 1;
    }
    std::cout << "SDL Initialized" << std::endl;
    std::cout << "SDL video driver: "
              << SDL_GetCurrentVideoDriver()
              << std::endl;

    // Create OpenGL SDL window & verify 
    SDL_Window* window = SDL_CreateWindow("Perception Sandbox - Vector Demo",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          WINDOW_WIDTH,
                                          WINDOW_HEIGHT,
                                          SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    if(window == nullptr)
    {
        std::cerr << "SDL_CreateWindow Failed: " << SDL_GetError() << "\n";
        SDL_Quit();
        return 1;
    } 
    std::cout << "Built SDL Window" << std::endl;

    // Create OpenGL context (renderer) & verify
    SDL_GLContext context = SDL_GL_CreateContext(window);
    if(context == nullptr)
    {
        std::cerr << "SDL_GL_CreateContext failed: " << SDL_GetError() << '\n';
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Run visual
    bool running = true;
    while(running)
    {
        // Check for exit
        SDL_Event event;
        while(SDL_PollEvent(&event))
        {
            running = (event.type != SDL_QUIT);
        }

        // Clear opengl color buffer
        glClear(GL_COLOR_BUFFER_BIT);

        // Put OpenGL in line drawing mode
        Set_draw_color(EColors::White);
        glPointSize(10.0f);
        glBegin(GL_LINES);

        // X axis
        Set_draw_color(EColors::Red_pastel);
        glVertex2d(-WINDOW_WIDTH/2, 0.0);
        glVertex2d(WINDOW_WIDTH/2, 0.0);

        // Y axis
        Set_draw_color(EColors::Blue_pastel);
        glVertex2d(0.0, -WINDOW_HEIGHT/2);
        glVertex2d(0.0, WINDOW_HEIGHT/2);

        glEnd();

        // Draw a 10x10 pixel point moving around
        glPointSize(10.0f);
        glBegin(GL_POINTS);

        static Vector2 position(0.0, 0.0);
        static Random random_motion(42);
        Vector2 velocity(random_motion.Gaussian(0, 0.025), 
                         random_motion.Gaussian(0, 0.025));
        if(std::abs(position.Magnitude()) > 1)
        {
            position.X = 0; 
            position.Y = 0;
        }
        Set_draw_color(EColors::Green);
        glVertex2d(position.X, position.Y);
        glEnd();
        position += velocity;

        // Checkout a visual of normalized and magnitude
        Vector2 v(0.6, 0.4);
        Set_draw_color(EColors::White);
        glBegin(GL_LINES);
        glVertex2d(0.0, 0.0); // origin
        glVertex2d(v.X, v.Y); // Vector endpoint
        glVertex2d(v.X, v.Y); // Endpoint of triangle
        glVertex2d(v.X, 0);   // back to x-axis

        // Normalized vector 
        glVertex2d(0.0, 0.0);
        glVertex2d(v.Normalized().X, v.Normalized().Y);
        glEnd();

        glPointSize(8.0f);
        Set_draw_color(EColors::Red);
        glBegin(GL_POINTS);
        glVertex2d(v.X, v.Y); // Red original
        Set_draw_color(EColors::Blue);
        glVertex2d(v.Normalized().X, v.Normalized().Y); // Blue normilized
        glEnd();

        // Draw unit circle
        // How many radians per/sec do I want this circle to be moving at? 
        // Lets say we want a line moving in the path of a unit circle at 1 rad/sec
        static uint64_t last_t = SDL_GetTicks64(); // in ms
        uint64_t now = SDL_GetTicks64();

        // Update line moving around unit circle at pi/2 rad/sec
        double rad_sec = std::numbers::pi / 2;  
        double frame_sec = 24;
        double rad_frame = rad_sec * 1/frame_sec; // radian/frame
        Matrix rotation(2,2);
        rotation(0,0) =  std::cos(rad_frame);
        rotation(0,1) = -std::sin(rad_frame);
        rotation(1,0) =  std::sin(rad_frame);
        rotation(1,1) =  std::cos(rad_frame);
        static Vector2 unit_circle(1,0);

        double interval_ms = 1.0 / static_cast<double>(frame_sec) * 1000; 
        if(now - last_t > interval_ms)
        {
            unit_circle = rotation*unit_circle;
            last_t = now;
        }

        glBegin(GL_LINES);
        Set_draw_color(EColors::Yellow);
        glVertex2d(0,0);
        glVertex2d(unit_circle.X, unit_circle.Y);
        glVertex2d(unit_circle.X, unit_circle.Y);
        glVertex2d(unit_circle.X, 0);
        glEnd();

        // Swap buffers to update frame
        SDL_GL_SwapWindow(window);
    }

    return 0;
}