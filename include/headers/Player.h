#include "SDL_utils.h"
#include "Laser.h"

class Player
{
public:
    Player();
    void movement();
    void shoot(std::vector <Laser>& playerLaser);
    bool load(std::string path);
    void loadImage();

    SDL_Rect* getPos() {return &pos;};
    // int getPositionY() { return pos.y; }
    // int getPositionX() { return pos.x; }
    int getWidth() { return SIZE_WIDTH; }
    int getHeight() { return SIZE_HEIGHT; }
    

private:
    SDL_Rect pos;
    SDL_Texture* rocket;

    const int SIZE_WIDTH = 40;
    const int SIZE_HEIGHT = 40;

    const int START_X = SCREEN_WIDTH / 2;
    const int START_Y = SCREEN_HEIGHT / 4 * 3;

    const int SPEED = 60;
};