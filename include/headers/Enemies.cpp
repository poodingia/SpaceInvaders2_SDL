#include "Enemies.h"

Enemies::Enemies(int enemiesRow)
{
    add(1);
    if (!load("res/Enemies.png"))
    {
        logSDLError(std::cout, "Enemies texture", true);
    }
}

void Enemies::add(int enemiesRow)
{
    int spawnX, spawnY = 0, enemyWidth = 40, enemyHeight = 40;
    for (int j = 0; j < enemiesRow; j++)
    {
        if (moveDirection == RIGHT)
            spawnX = 100;
        else
            spawnX = 500;
        std::vector<Enemy> army;
        for (int i = 0; i < enemiesColumn; i++)
        {
            SDL_Rect temp = {spawnX, spawnY, enemyWidth, enemyHeight};
            Enemy enemy(temp, moveSpeed, moveDirection);
            army.push_back(enemy);
            spawnX += 100;
        }
        spawnY += 50;
        armies.push_back(army);
    }
}

void Enemies::upgrade(int &level)
{
    if(steps >= changes || left == 0 && level != 1)
    {
        steps = 0;
        level++;
        moveDirection = 2 - moveDirection;
        if(level > 3)
        {
            moveSpeed++;
            level = 1;
        }
        add(level);
    }
}

void Enemies::moveEnemeies()
{
    bool switchDirection = false;

    for (auto &i : armies)
    {
        for (auto &y : i)
        {
            left++;
            switch (y.direction)
            {
            case LEFT:
                y.pos.x -= y.movementSpeed;
                break;

            case RIGHT:
                y.pos.x += y.movementSpeed;
                break;
            }
        }
    }
    totalMove += moveSpeed;
    if (totalMove >= 400)
    {
        switchDirection = true;
        steps++;
    }
    if (switchDirection)
    {
        for (auto &i : armies)
        {
            for (auto &y : i)
            {
                y.direction = 2 - y.direction;
                y.pos.y += downSpeed;
            }
        }
        totalMove = 0;
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
