#include <SDL2/SDL.h>
#include <iostream>

int main()
{
    std::cout << "Before SDL_Init" << std::endl;

    if(SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cerr << "SDL_Init failed: " << SDL_GetError() << std::endl;
        return 1;
    }
    std::cout << "SDL_Init succeeded" << std::endl;
    std::cout << "Video driver: " 
              << SDL_GetCurrentVideoDriver() 
              << std::endl;

    SDL_Window* window = SDL_CreateWindow("SDL Test",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          800,
                                          600,
                                          SDL_WINDOW_OPENGL);
    if(window == nullptr)
    {
        std::cerr << "SDL_CreateWindow failed: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }
    std::cout << "SDL_CreateWindow succeeded" << std::endl;

    SDL_GLContext context = SDL_GL_CreateContext(window);
    if (context == nullptr)
    {
        std::cerr << "SDL_GL_CreateContext failed: "
                  << SDL_GetError() << '\n';

        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    bool running = true;
    while(running)
    {
        SDL_Event event;
        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
            {
                running = false;
            }
        }

        SDL_Delay(10);
    }

    SDL_DestroyWindow(window);
    SDL_GL_DeleteContext(context);
    SDL_Quit();

    return 0;
}