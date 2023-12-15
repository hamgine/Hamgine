#pragma once
#include <iostream>
#include <stdio.h>
#define SDL_MAIN_HANDLED
#include <SDL.h>
#include "math.cpp";
class entity {
public:
    Vector2 position = Vector2(0, 0);
    SDL_Surface* texture;
};
int entityCount = 0;
entity *entities = (entity*)malloc(sizeof(entity) * 1024);
entity createEntity(Vector2 startPos, SDL_Surface* sprite) 
{
    entity x;
    x.position = startPos;
    x.texture = sprite;
    entities[entityCount] = x;
    entityCount++;
    return x;
}

SDL_Surface* screen;
SDL_Window* window;
SDL_Renderer* renderer;

//test
SDL_Surface* image = SDL_LoadBMP("cigo.bmp");






int createWindow(const char* title, int width, int height) {
    window = SDL_CreateWindow(title,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width, height,   0);
    return 0;
}
void Draw() {
    SDL_FillRect(screen, NULL, 0x000000);


    int i = 0;
    while (i < entityCount)
    {
        SDL_Rect rect;
        entity y = entities[i];
        rect.x = y.position.x;
        rect.y = y.position.y;
        rect.w = 0;
        rect.h = 0;
        SDL_BlitSurface(y.texture, NULL, screen, &rect);
        i++;
    }


    SDL_UpdateWindowSurface(window);
}
int main()
{
    //set main
    SDL_SetMainReady();
    //init sdl
    if ((SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) == -1)) {
        printf("Could not initialize SDL: %s.\n", SDL_GetError());
        exit(-1);
    }
    //init window
    createWindow("Hamgine Test",1280,720);
    renderer = SDL_GetRenderer(window);
    //cleanup on quit
    atexit(SDL_Quit);
    //create surface
    screen = SDL_GetWindowSurface(window);
    if (screen == NULL) {
        fprintf(stderr, "Couldn't set video mode: %s\n",
            SDL_GetError());
        exit(1);
    }

    entity test = createEntity(Vector2(0,0),image);

    //process events
    bool run = true;
    while (run)
    {
        SDL_Event e;
        while (SDL_PollEvent(&e) > 0)
        {
            switch (e.type)
            {
            case SDL_QUIT:
                run = false;
                break;
            }
        }
        Draw();
    }
    return 0;
}