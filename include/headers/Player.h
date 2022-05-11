#include "SDL_utils.h"
#include "Laser.h"

class Player
{
public:
    Player();
    void movement();
    void shoot(std::vector<Laser> &playerLaser);
    bool load(std::string path);
    void loadImage();

    SDL_Rect *getPos() { return &pos; };
    void move(std::vector<Laser> &playerLaser);
    void setMode();
    void reset();

    std::string enhance[5] = {"Normal",
                              "Double Bullet", 
                              "Bullet Speed",
                              "Smaller Size", 
                              "Ship Speed"};

    int mode;
private:
    SDL_Rect pos;
    SDL_Texture *rocket;

    int SIZE_WIDTH = 40;
    int SIZE_HEIGHT = 40;

    const int START_X = SCREEN_WIDTH / 2;
    const int START_Y = SCREEN_HEIGHT / 4 * 3;

    int bulletSpeed = 10;
    int SPEED = 60;
};