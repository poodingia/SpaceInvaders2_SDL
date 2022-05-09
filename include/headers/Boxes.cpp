#include "Boxes.h"

Boxes::Boxes()
{
    
}

void Boxes::add(SDL_Rect box)
{
    srand(time(NULL));

    Box one(box, SPEED, rand() % 3);
    boxes.push_back(one);
}

bool Boxes::load(std::string path)
{
    SDL_Surface *surface = IMG_Load(path.c_str());
    if (surface == nullptr)
    {
        logSDLError(std::cout, path, true);
        return false;
    }
    else
    {
        redBox = SDL_CreateTextureFromSurface(g_renderer, surface);
    }
    SDL_FreeSurface(surface);
    return true;
}

void Boxes::loadImage()
{
    for(auto &i : boxes)
    {
        SDL_RenderCopy(g_renderer, redBox, NULL, &i.box);
    }
}

void Boxes::move()
{
    for(auto &i:boxes)
    {
        i.box.y += SPEED;
    }
}