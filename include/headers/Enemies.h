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
    Enemies(int enemiesRow);
    void moveEnemeies();
    bool load(std::string path);
    void loadImage();

    int enemiesColumn = 8;
    int downSpeed = 60;
    int totalMove = 0;
    int moveSpeed = 10;

    std::vector<std::vector <Enemy>> armies;
    SDL_Texture* enemyTexture;
};