#include "Game.h"

void Game::start()
{

    initSDL("Space Invaders Forever");
    if (!load())
    {
        quit();
        return;
    }
    init();
    boxes.load("res/box.png");
    while (isRunning)
    {
        Player player;
        SDL_Delay(100);
        Enemies enemies(level);
        playMusic();
        while (isPlaying)
        {

            Uint32 starts = SDL_GetTicks();
            player.reset();
            player.setMode();
            while (SDL_PollEvent(&g_event))
            {
                if (g_event.type == SDL_QUIT)
                {
                    isPlaying = false;
                    isRunning = false;
                    quit();
                    break;
                }
                if (g_event.type == SDL_KEYDOWN && g_event.key.repeat == 0)
                {
                    player.movement();
                    player.shoot(playerLaser);
                }
                if (g_event.key.keysym.sym == SDLK_SPACE && g_event.type == SDL_KEYDOWN)
                {
                    shot++;
                }
            }
            enemies.upgrade(level);
            enemies.moveEnemeies();
            enemyshoot(enemies.armies);
            moveLaser();
            checkCollision(enemies.armies);
            boxes.move();
            player.move(playerLaser);
            checkBox(player);

            loadImage();
            drawLaser();
            boxes.loadImage();
            enemies.loadImage();
            player.loadImage();
            displayText("Hit Rate: " + std::to_string((int)hitRate) + " %", SCREEN_WIDTH - 250, 700);
            displayText("Score: " + std::to_string((int)hit), 20, 700);
            displayTextColor(player.enhance[player.mode], 590, 800, 255, 255, 0);
            SDL_RenderPresent(g_renderer);

            if (gameOver(enemies.armies, player))
            {
                Mix_PauseMusic();
                playSound("music/gameover.wav");
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
            reset();
        }
    }
    quit();
}

void Game::moveLaser()
{

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
        switch (i.mode)
        {
        case 1:
            SDL_SetRenderDrawColor(g_renderer, 255, 255, 0, SDL_ALPHA_OPAQUE);
            break;
        case 2:
            SDL_SetRenderDrawColor(g_renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
            break;
        case 3:
            SDL_SetRenderDrawColor(g_renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);
            break;
        default:
            break;
        }
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
    if (shot > 0)
        hitRate = (float)(hit * 100) / shot;
    else
    {
        shot = 0;
        hitRate = 0;
        hit = 0;
    }

    for (int i = 0; i < playerLaser.size(); i++)
    {
        for (int y = 0; y < enemies.size(); y++)
        {
            for (int j = 0; j < enemies[y].size(); j++)
                if (SDL_HasIntersection(&playerLaser[i].pos, &enemies[y][j].pos) == SDL_TRUE)
                {
                    hit++;
                    SDL_Rect temp = enemies[y][j].pos;
                    playerLaser.erase(playerLaser.begin() + i);
                    enemies[y].erase(enemies[y].begin() + j);
                    playSound("music/invaderkilled.wav");
                    SDL_RenderCopy(g_renderer, explosion, NULL, &temp);
                    if (hit > 0 && hit % 10 == 0)
                    {
                        boxes.add(temp);
                    }
                    boxes.loadImage();
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
        enemiesLaser.push_back(Laser({startXPos, startYPos, sizeWidth, sizeHeight}, movementSpeed, dir, 0));
    }
}

bool Game::gameOver(std::vector<std::vector<Enemy>> &enemies, Player player)
{
    for (auto &i : enemies)
    {
        if (i.size() > 0)
        {
            if (i[0].pos.y + i[0].pos.h >= SCREEN_HEIGHT * 3 / 4)
            {
                return true;
            }
        }
    }

    for (int i = 0; i < enemiesLaser.size(); i++)
    {
        if (SDL_HasIntersection(&enemiesLaser[i].pos, player.getPos()) == SDL_TRUE)
        {
            return true;
        }
    }
    return false;
}

bool Game::load()
{
    SDL_Surface *surface = IMG_Load("res/background.jpg");
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
    SDL_RenderCopy(g_renderer, startScreen, NULL, NULL);
    displayText("PRESS SPACE BAR TO BEGIN", 380, 750);
    SDL_RenderPresent(g_renderer);
    while (true)
    {
        if (SDL_WaitEvent(&g_event) != 0 && (g_event.type == SDL_KEYDOWN) && g_event.key.keysym.sym == SDLK_SPACE)
            return;
        if (g_event.type == SDL_QUIT)
        {
            isRunning = false;
            return;
        }
    }
    return;
}

void Game::quit()
{
    SDL_DestroyTexture(startScreen);
    SDL_DestroyTexture(background);
    SDL_DestroyTexture(explosion);
    quitSDL();
}

void Game::save()
{

    std::ofstream outfile;
    outfile.open("content/score.txt", std::fstream::app);
    SDL_StartTextInput();
    std::string text = "";
    while (true)
    {
        SDL_SetRenderDrawColor(g_renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(g_renderer);
        loadImage();
        displayText("ENTER YOUR NICKNAME:", 100, 200);
        displayText(text + '_', 500, 200);
        SDL_RenderPresent(g_renderer);
        if (SDL_WaitEvent(&g_event) != 0)
        {

            if (g_event.type == SDL_QUIT)
            {
                isRunning = false;
                quit();
                return;
            }
            if (g_event.type == SDL_TEXTINPUT && *g_event.text.text != ' ')
            {
                text += g_event.text.text;
            }
            else if (g_event.type == SDL_KEYDOWN)
            {
                if (g_event.key.keysym.sym == SDLK_RETURN)
                {
                    if (text.size() == 0)
                        text = "anonymous";
                    outfile << text << ' ' << hit << "\n";
                    outfile.close();
                    break;
                }

                else if (g_event.key.keysym.sym == SDLK_BACKSPACE && text.size() > 0)
                {
                    text.pop_back();
                }
            }
        }
    }
    std::ifstream infile("content/score.txt");
    std::string name;
    int hit, y = 200;
    scoreBoard.clear();
    while (true)
    {
        y = 200;
        SDL_SetRenderDrawColor(g_renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(g_renderer);
        loadImage();
        if (infile.is_open())
        {
            while (infile >> name)
            {
                if (name.size() == 0)
                    continue;
                infile >> hit;
                scoreBoard.insert({hit, name});
            }
        }
        infile.close();
        displayText("HIGHSCORE", 530, y - 100);
        displayText("NAME", 200, y);
        displayText("HIT", 1000, y);
        y += 100;
        for (auto &[key, val] : scoreBoard)
        {
            displayText(val, 200, y);
            displayText(std::to_string(key), 1000, y);
            y += 40;
        }
        SDL_RenderPresent(g_renderer);
        if (SDL_WaitEvent(&g_event) != 0)
        {
            if (g_event.type == SDL_QUIT)
            {
                isRunning = false;
                quit();
                return;
            }
            if (g_event.type == SDL_KEYDOWN)
            {
                if (g_event.key.keysym.sym == SDLK_RETURN)
                {
                    break;
                }
            }
        }
    }
}

void Game::reset()
{
    save();
    level = 1;
    shot = 0;
    hit = 0;
    hitRate = 0;
    SDL_SetRenderDrawColor(g_renderer, 0, 0, 0, 255);
    SDL_RenderClear(g_renderer);
    loadImage();
    isRunning = isContinue(&isPlaying);
    enemiesLaser.clear();
    playerLaser.clear();
    boxes.boxes.clear();
}

void Game::checkBox(Player &player)
{
    int index = 0;
    for (auto &i : boxes.boxes)
    {
        if (SDL_HasIntersection(player.getPos(), &i.box) == SDL_TRUE)
        {
            srand(time(NULL));
            player.mode = rand() % 4 + 1;
            boxes.boxes.erase(boxes.boxes.begin() + index);
            playSound("music/bonus.wav");
        }
        index++;
    }
}