#include "Player.h"

Player::Player()
{
    pos = {START_X, START_Y, SIZE_WIDTH, SIZE_HEIGHT};
    if (!load("res/player.png"))
    {
        logSDLError(std::cout, "Player texture", true);
    }
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
    int bulletSpeed = 10;
    if (g_event.key.keysym.sym == SDLK_SPACE && g_event.type == SDL_KEYDOWN)
    {
        SDL_Rect temp = {pos.x + SIZE_WIDTH / 2, pos.y + 20, 5, 20};
        Laser bullet(temp, bulletSpeed, UP);
        playerLaser.push_back(bullet);
        playSound("music/shoot.wav");
    }
}