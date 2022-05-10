#include "SDL_utils.h"

struct Laser
{
    Laser(SDL_Rect pos_, int movementSpeed_, int dir_, int mode_)
    {
        pos = pos_;
        movementSpeed = movementSpeed_;
        direction = dir_;
        mode = mode_;
    }

    SDL_Rect pos;
    int movementSpeed; 
    int direction; 
    int mode;
};

