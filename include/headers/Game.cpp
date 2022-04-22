#include "Game.h"

void Game::start()
{

    initSDL("Game v1.0");
    if (!load())
    {
        quitSDL();
        return;
    }
    init();
    while (isRunning)
    {
        playMusic();
        SDL_Delay(100);
        Player player;
        Enemies enemies(level);
        while (isPlaying)
        {

            Uint32 starts = SDL_GetTicks();
            while (SDL_PollEvent(&g_event))
            {
                if (g_event.type == SDL_QUIT)
                {
                    isPlaying = false;
                    isRunning = false;
                }
                if (g_event.type == SDL_KEYDOWN)
                {
                    player.movement();
                    player.shoot(playerLaser);
                }
            }
            shot = playerLaser.size();
            enemies.moveEnemeies();
            enemyshoot(enemies.armies);
            moveLaser();
            checkCollision(enemies.armies);

            loadImage();
            drawLaser();
            enemies.loadImage();
            player.loadImage();
            displayText("Level: " + std::to_string(level), 20, 20);
            displayText("Bullet shot: " + std::to_string(shot), SCREEN_WIDTH - 250, 20);
            SDL_RenderPresent(g_renderer);
            if (gameOver(enemies.armies, player))
            {
                SDL_Delay(500);
                isPlaying = false;
            }

            /*************Handle FPS*************/
            Uint32 end = SDL_GetTicks() - starts;
            if (frameDelay > end)
            {
                SDL_Delay(frameDelay - end);
            }
            /************************************/
        }
        if (isRunning)
        {
            if (win)
            {
                level++;
                if (level >= 4)
                    level = 4;
                isPlaying = true;
                enemiesLaser.clear();
                playerLaser.clear();
            }
            else
            {
                level = 1;
                shot = 0;
                SDL_SetRenderDrawColor(g_renderer, 0, 0, 0, 255);
                SDL_RenderClear(g_renderer);
                loadImage();
                isRunning = isContinue(&isPlaying);
                enemiesLaser.clear();
                playerLaser.clear();
            }
        }
    }

    quitSDL();
}

void Game::moveLaser()
{
    for (auto &i : playerLaser)
    {
        i.pos.y -= i.movementSpeed;
    }

    for (auto &i : enemiesLaser)
    {
        i.pos.y += i.movementSpeed;
    }
}

void Game::drawLaser()
{
    for (auto &i : playerLaser)
    {
        SDL_Rect temp = i.pos;
        SDL_SetRenderDrawColor(g_renderer, 255, 255, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderFillRect(g_renderer, &temp);
    }

    for (auto &i : enemiesLaser)
    {
        SDL_Rect temp = i.pos;
        SDL_SetRenderDrawColor(g_renderer, 0, 255, 255, SDL_ALPHA_OPAQUE);
        SDL_RenderFillRect(g_renderer, &temp);
    }
}

void Game::checkCollision(std::vector<std::vector<Enemy>> &enemies)
{
    for (int i = 0; i < playerLaser.size(); i++)
    {
        for (int y = 0; y < enemies.size(); y++)
        {
            for (int j = 0; j < enemies[y].size(); j++)
                if (SDL_HasIntersection(&playerLaser[i].pos, &enemies[y][j].pos) == SDL_TRUE)
                {
                    SDL_Rect temp = enemies[y][j].pos;
                    playerLaser.erase(playerLaser.begin() + i);
                    enemies[y].erase(enemies[y].begin() + j);
                    playSound("music/invaderkilled.wav");
                    SDL_RenderCopy(g_renderer, explosion, NULL, &temp);
                    SDL_RenderPresent(g_renderer);
                    SDL_Delay(25);
                }
        }
    }
}

void Game::enemyshoot(std::vector<std::vector<Enemy>> &enemies)
{
    srand(time(0));
    Uint32 startTime = SDL_GetTicks();
    int randRow = rand() % enemies.size();
    if (enemies[randRow].size() == 0)
        return;
    int randEnemy = rand() % enemies[randRow].size();
    int startXPos = enemies[randRow][randEnemy].pos.x + 20;
    int startYPos = enemies[randRow][randEnemy].pos.y;

    int sizeWidth = 5;
    int sizeHeight = 20;
    int movementSpeed = 8;
    int dir = DOWN;

    if (startTime % 15 == 0)
    {
        enemiesLaser.push_back(Laser({startXPos, startYPos, sizeWidth, sizeHeight}, movementSpeed, dir));
    }
}

bool Game::gameOver(std::vector<std::vector<Enemy>> &enemies, Player player)
{
    int left = 0;
    for (auto &i : enemies)
    {
        left += i.size();
        if (i.size() > 0)
        {
            if (i[0].pos.y + i[0].pos.h >= SCREEN_HEIGHT * 3 / 4)
            {
                win = false;
                return true;
            }
        }
    }
    if (left == 0)
    {
        win = true;
        return true;
    }
    for (int i = 0; i < enemiesLaser.size(); i++)
    {
        if (SDL_HasIntersection(&enemiesLaser[i].pos, player.getPos()) == SDL_TRUE)
        {
            win = false;
            return true;
        }
    }
    return false;
}

bool Game::load()
{
    SDL_Surface *surface = IMG_Load("res/background.png");
    SDL_Surface *startscreen = IMG_Load("res/startscreen.jpg");
    SDL_Surface *explosurface = IMG_Load("res/explosion.png");
    if (surface == nullptr || startscreen == nullptr)
    {
        logSDLError(std::cout, "load background", true);
        return false;
    }
    else
    {
        background = SDL_CreateTextureFromSurface(g_renderer, surface);
        startScreen = SDL_CreateTextureFromSurface(g_renderer, startscreen);
        explosion = SDL_CreateTextureFromSurface(g_renderer, explosurface);
    }
    SDL_FreeSurface(surface);
    SDL_FreeSurface(startscreen);
    SDL_FreeSurface(explosurface);
    return true;
}

void Game::loadImage()
{
    SDL_SetRenderDrawColor(g_renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(g_renderer);
    SDL_RenderCopy(g_renderer, background, NULL, NULL);
    SDL_SetRenderDrawColor(g_renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawLine(g_renderer, 0, SCREEN_HEIGHT * 3 / 4, SCREEN_WIDTH, SCREEN_HEIGHT * 3 / 4);
}

void Game::init()
{
    Uint32 start = SDL_GetTicks();
    SDL_RenderCopy(g_renderer, startScreen, NULL, NULL);
    SDL_RenderPresent(g_renderer);
    while (true)
    {
        if (SDL_WaitEvent(&g_event) != 0 && (g_event.type == SDL_KEYDOWN))
            return;
        if (g_event.type == SDL_QUIT)
        {
            isRunning = false;
            return;
        }
    }
    return;
}
