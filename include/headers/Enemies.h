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
    void add(int enemiesRow);
    void upgrade(int &level);
    bool load(std::string path);
    void loadImage();

    int enemiesColumn = 8;
    int downSpeed = 40;
    int totalMove = 0;
    int moveSpeed = 8;
    int steps = 0;
    int changes = 4;
    int left = 0;
    int moveDirection = RIGHT;

    std::vector<std::vector <Enemy>> armies;
    SDL_Texture* enemyTexture;
};