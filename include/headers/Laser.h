#include "SDL_utils.h"

struct Laser
{
    Laser(SDL_Rect pos_, int movementSpeed_, int dir)
    {
        pos = pos_;
        movementSpeed = movementSpeed_;
        direction = dir;
    }

    SDL_Rect pos;
    int movementSpeed; 
    int direction; 
    int level = 1;
};

