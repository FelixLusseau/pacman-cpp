#include "../include/ThePacman.hpp"

ThePacman::ThePacman() : Character() {
    /* right */
    sprite_[0] = {18, 90, 16, 16};
    sprite_[1] = {34, 90, 14, 16};
    /* left */
    sprite_[2] = {48, 90, 16, 16};
    sprite_[3] = {62, 90, 14, 16};
    /* up */
    sprite_[4] = {108, 90, 16, 16};
    sprite_[5] = {126, 94, 16, 12};
    /* down */
    sprite_[6] = {76, 90, 16, 16};
    sprite_[7] = {92, 94, 16, 12};

    cur_sprite_ = {4, 90, 16, 16};

    position_ = {34, 160, 30, 30};

    die_animation[0] = {4, 90, 16, 16};
    die_animation[1] = {4, 106, 16, 16};
    die_animation[2] = {23, 106, 16, 16};
    die_animation[3] = {42, 106, 16, 16};
    die_animation[4] = {61, 106, 16, 16};
    die_animation[5] = {80, 106, 16, 16};
    die_animation[6] = {99, 106, 14, 16};
    die_animation[7] = {116, 106, 10, 16};
    die_animation[8] = {129, 106, 6, 16};
    die_animation[9] = {138, 106, 2, 16};
    die_animation[10] = {143, 106, 16, 16};
}

int mv_x{0}, mv_y{0};
SDL_Scancode prec_key{SDL_SCANCODE_UNKNOWN};

void ThePacman::move(const Uint8 *keys, int animation, std::vector<std::vector<Tile>> map, SDL_Rect bg) {

    SDL_Rect sp = cur_sprite_;

    if (keys[SDL_SCANCODE_RIGHT] || prec_key == SDL_SCANCODE_RIGHT) {
        prec_key = SDL_SCANCODE_RIGHT;
        cur_sprite_ = sprite_[0 + animation];
        mv_x = 2;
    }
    if (keys[SDL_SCANCODE_LEFT] || prec_key == SDL_SCANCODE_LEFT) {
        prec_key = SDL_SCANCODE_LEFT;
        cur_sprite_ = sprite_[2 + animation];
        mv_x = -2;
    }
    if (keys[SDL_SCANCODE_DOWN] || prec_key == SDL_SCANCODE_DOWN) {
        prec_key = SDL_SCANCODE_DOWN;
        cur_sprite_ = sprite_[4 + animation];
        mv_y = 2;
    }
    if (keys[SDL_SCANCODE_UP] || prec_key == SDL_SCANCODE_UP) {
        prec_key = SDL_SCANCODE_UP;
        cur_sprite_ = sprite_[6 + animation];
        mv_y = -2;
    }
    // cur_sprite_=sp;
    this->changePosition(position_.x + mv_x, position_.y + mv_y, map, bg);

    // std::cout<<position_.x<<" "<<position_.y<<std::endl;
}

void ThePacman::die(SDL_Surface *plancheSprites, SDL_Rect *src_bg, SDL_Surface *win_surf, SDL_Rect *bg, SDL_Window *pWindow) {

    int x = position_.x;
    int y = position_.y;

    for (int i = 0; i < 11; i++) { // animation

        if (i == 9) { // n°9 est un rectangle qui requiert une largeur différente des autres sprites
            position_.w = 4;
            position_.x += 10;
        } else if (i > 9) {
            position_.w = 32;
            position_.x = x;
        }

        SDL_SetColorKey(plancheSprites, false, 0);
        SDL_BlitScaled(plancheSprites, src_bg, win_surf, bg);
        SDL_BlitScaled(plancheSprites, &die_animation[i], win_surf, &position_);
        SDL_UpdateWindowSurface(pWindow);
        SDL_Delay(200);
    }

    SDL_UpdateWindowSurface(pWindow);
}