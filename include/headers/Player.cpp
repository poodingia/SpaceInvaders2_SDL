#include "Player.h"

Player::Player()
{
    pos = {START_X, START_Y, SIZE_WIDTH, SIZE_HEIGHT};
    if (!load("res/player.png"))
    {
        logSDLError(std::cout, "Player texture", true);
    }
    mode = 0;
}

bool Player::load(std::string path)
{
    SDL_Surface *surface = IMG_Load(path.c_str());
    if (surface == nullptr)
    {
        logSDLError(std::cout, path, true);
        return false;
    }
    else
    {
        rocket = SDL_CreateTextureFromSurface(g_renderer, surface);
    }
    SDL_FreeSurface(surface);
    return true;
}

void Player::loadImage()
{
    SDL_RenderCopy(g_renderer, rocket, NULL, &pos);
}

void Player::movement()
{
    const Uint8 *currentKeyStates = SDL_GetKeyboardState(NULL);
    if (currentKeyStates[SDL_SCANCODE_LEFT])
    {
        pos.x -= SPEED;
    }
    else if (currentKeyStates[SDL_SCANCODE_RIGHT])
    {
        pos.x += SPEED;
    }
    if (pos.x <= 40)
        pos.x += SPEED;
    if (pos.x >= 1200)
        pos.x -= SPEED;
}

void Player::shoot(std::vector<Laser> &playerLaser)
{
    if (g_event.key.keysym.sym == SDLK_SPACE && g_event.type == SDL_KEYDOWN)
    {
        SDL_Rect temp = {pos.x + SIZE_WIDTH / 2, pos.y + 20, 5, 20};
        Laser bullet(temp, bulletSpeed, UP);
        switch (mode)
        {
        case 1:
            playerLaser.push_back(bullet);
            break;
        case 2:
            bulletSpeed++;
            break;
        case 3:
            pos.h = 30;
            pos.w = 30;
            break;
        case 4:
            SPEED += 2;
            break;
        default:
            break;
        }
        playerLaser.push_back(bullet);
        playSound("music/shoot.wav");
    }
}

void Player::move(std::vector<Laser> &playerLaser)
{
    for (auto &i : playerLaser)
    {
        i.pos.y -= i.movementSpeed;
    }
}