#include "SDL_utils.h"

struct Enemy
{
    Enemy(SDL_Rect pos_, int movementSpeed_, int dir_)
    {
        pos = pos_;
        movementSpeed = movementSpeed_;
        direction = dir_;
    }

    SDL_Rect pos; 
    int movementSpeed;
    int direction;
};

class Enemies
{
public:
    Enemies();
    void moveEnemeies();
    bool load(std::string path);
    void loadImage();

    int enemiesRow = 4;
    int enemiesColumn = 8;
    int downSpeed = 60;

    std::vector<std::vector <Enemy>> armies;
    SDL_Texture* enemyTexture;
};