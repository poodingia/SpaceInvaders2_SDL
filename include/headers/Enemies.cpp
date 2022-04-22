#include "Enemies.h"

Enemies::Enemies( int enemiesRow)
{
    int spawnX = 100;
    int spawnY = 100;
    int enemyWidth = 40;
    int enemyHeight = 40;
    for (int j = 0; j < enemiesRow; j++)
    {
        spawnX = 100;
        std::vector<Enemy> army;
        for (int i = 0; i < enemiesColumn; i++)
        {
            SDL_Rect temp = {spawnX, spawnY, enemyWidth, enemyHeight};
            Enemy enemy(temp, 10, RIGHT);
            army.push_back(enemy);
            spawnX += 100;
        }
        spawnY += 50;
        armies.push_back(army);
    }

    if (!load("res/Enemies.png"))
    {
        logSDLError(std::cout, "Enemies texture", true);
    }
}

void Enemies::moveEnemeies()
{
    bool switchDirection = false;
    int moveDirection;
    for (auto &i : armies)
    {
        if(i.size() > 0)
            moveDirection = i[0].direction;
    }
    switch (moveDirection)
    {
    case LEFT:
        for (auto &i : armies)
        {
            for (auto &y : i)
                y.pos.x -= y.movementSpeed;
        }
        break;

    case RIGHT:
        for (auto &i : armies)
        {
            for (auto &y : i)
                y.pos.x += y.movementSpeed;
        }
        break;
    }

    for (auto &i : armies)
    {
        if (i[0].pos.x <= 40)
        {
            switchDirection = true;
            break;
        }
        if (i[i.size() - 1].pos.x >= SCREEN_WIDTH - 40 - 40)
        {
            switchDirection = true;
            break;
        }
    }
    if (switchDirection)
        for (auto &i : armies)
        {
            for (auto &y : i)
            {
                y.direction = 2 - y.direction;
                y.pos.y += downSpeed;
            }
        }
}

bool Enemies::load(std::string path)
{
    SDL_Surface *surface = IMG_Load(path.c_str());
    if (surface == nullptr)
    {
        logSDLError(std::cout, path, true);
        return false;
    }
    else
    {
        enemyTexture = SDL_CreateTextureFromSurface(g_renderer, surface);
    }
    SDL_FreeSurface(surface);
    return true;
}

void Enemies::loadImage()
{
    for (auto &i : armies)
    {
        for (auto &y : i)
        {
            SDL_Rect temp = y.pos;
            SDL_RenderCopy(g_renderer, enemyTexture, NULL, &temp);
        }
    }
}
