#include "SDL_utils.h"

const int SPEED = 8;

struct Box
{
    Box(SDL_Rect box_, int movement_speed_, int mode_)
    {
        box = box_;
        movement_speed = movement_speed_;
        mode = mode_;
    }

    SDL_Rect box;
    int movement_speed;
    int mode;
};

struct Boxes
{
    Boxes();
    void move();
    void add(SDL_Rect box);
    bool load(std::string path);
    void loadImage();

    std::vector <Box> boxes;
    SDL_Texture* redBox;
};