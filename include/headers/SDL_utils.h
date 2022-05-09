#pragma once
#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <stdint.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

enum DIRECTION
{
    LEFT,
    UP,
    RIGHT,
    DOWN,
    TOTAL
};

extern SDL_Window *g_window;
extern SDL_Renderer *g_renderer;
extern SDL_Surface* g_icon;
extern SDL_Event g_event;

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 840;
const int SCREEN_BPP = 322;

void logSDLError(std::ostream &os, const std::string &msg, bool fatal = false);

void initSDL(std::string WINDOW_TILTE);

void quitSDL();

void waitUntilKeyPressed();

void displayText(std::string sentence, int x, int y);

void displayTextColor(std::string sentence, int x, int y, Uint8 red, Uint8 green, Uint8 blue);

void playMusic();

void playSound(std::string path);

void askPlayAgain();

bool isContinue(bool *isPlaying);

bool hit(SDL_Rect *x, SDL_Rect *y);
