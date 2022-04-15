#include "Game.h"


SDL_Window *g_window = NULL;
SDL_Renderer *g_renderer = NULL;
SDL_Surface *g_icon = NULL;
SDL_Event g_event;

int main(int argc, char *argv[])
{
    Game game;

    game.start();
    
    return 0;
}
