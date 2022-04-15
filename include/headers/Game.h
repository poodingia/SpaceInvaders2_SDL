#include "SDL_utils.h"
#include "Player.h"
#include "Enemies.h"

class Game
{
public:
    void start();
    void init();
    void quit();
    void moveLaser();
    void drawLaser();
    bool load();
    void loadImage();
    bool gameOver(std::vector<std::vector<Enemy>> &enemies, Player player);
    void checkCollision(std::vector<std::vector<Enemy>> &enemies);
    void enemyshoot(std::vector<std::vector<Enemy>> &enemies);

    std::vector<Laser> playerLaser;
    std::vector<Laser> enemiesLaser;

    SDL_Texture *startScreen;
    SDL_Texture *background;
    SDL_Texture *explosion;

    bool isRunning = true, isPlaying = true;
    const Uint32 FPS = 30;
    const Uint32 frameDelay = 1000 / FPS;
};
