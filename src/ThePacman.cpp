#include "../include/ThePacman.hpp"

ThePacman::ThePacman(const int x, const int y) : Character() {
    /* right */
    sprite_[0] = {18, 90, 16, 16};
    sprite_[1] = {34, 90, 14, 16};
    /* left */
    sprite_[2] = {48, 90, 16, 16};
    sprite_[3] = {62, 90, 14, 16};
    /* down */
    sprite_[4] = {108, 90, 16, 16};
    sprite_[5] = {126, 94, 16, 12};
    /* up */
    sprite_[6] = {76, 90, 16, 16};
    sprite_[7] = {92, 94, 16, 12};

    cur_sprite_ = {4, 90, 16, 16};

    position_ = {10 * x, 20 * y, 32, 32};
    init_position_ = {10 * x, 20 * y, 32, 32};

    lives_ = 3;

    die_animation_[0] = {4, 90, 16, 16};
    die_animation_[1] = {4, 106, 16, 16};
    die_animation_[2] = {23, 106, 16, 16};
    die_animation_[3] = {42, 106, 16, 16};
    die_animation_[4] = {61, 106, 16, 16};
    die_animation_[5] = {80, 106, 16, 16};
    die_animation_[6] = {99, 106, 14, 16};
    die_animation_[7] = {116, 106, 10, 16};
    die_animation_[8] = {129, 106, 6, 16};
    die_animation_[9] = {138, 106, 2, 16};
    die_animation_[10] = {143, 106, 16, 16};

    speed = 2;
}

void ThePacman::move(const Uint8 *keys, const int animation, const std::unique_ptr<Map> &map, const SDL_Rect bg) {

    // size of a tile of the map
    int tailleCaseX{map->getWidth()};
    int tailleCaseY{map->getHeight()};

    // collision at the corners with a sprite having a certain roundness
    int rondeur{3};

    // coordinates of the sprite corners
    int coinX[2] = {(position_.x + rondeur) / tailleCaseX, (position_.x + position_.w - rondeur) / tailleCaseX};
    int coinY[2] = {(position_.y + rondeur) / tailleCaseY, (position_.y + position_.w - rondeur) / tailleCaseY};

    int mv_x{0};
    int mv_y{0};

    // Buffer of pressed keys
    for (int i{0}; i < SDL_NUM_SCANCODES; i++) {
        if (keys[i]) {
            key_buffer_[i] = true;
            for (int j{0}; j < SDL_NUM_SCANCODES; j++) {
                if (i != j)
                    key_buffer_[j] = false;
            }
            break;
        }
    }

    if ((keys[SDL_SCANCODE_RIGHT] || prec_key == SDL_SCANCODE_RIGHT || key_buffer_[SDL_SCANCODE_RIGHT]) &&
        map->getMap()[coinY[0]][coinX[0] + 1] != Tile::Wall) {
        prec_key = SDL_SCANCODE_RIGHT;
        key_buffer_[SDL_SCANCODE_RIGHT] = false;
        mv_x = speed;
        position_.y = coinY[0] * tailleCaseY;
        if (changePosition(position_.x + mv_x, position_.y + mv_y, map->getMap(), bg))
            cur_sprite_ = sprite_[0 + animation];
    }
    if ((keys[SDL_SCANCODE_LEFT] || prec_key == SDL_SCANCODE_LEFT || key_buffer_[SDL_SCANCODE_LEFT]) &&
        map->getMap()[coinY[0]][coinX[1] - 1] != Tile::Wall) {
        prec_key = SDL_SCANCODE_LEFT;
        key_buffer_[SDL_SCANCODE_LEFT] = false;
        mv_x = -speed;
        position_.y = coinY[0] * tailleCaseY;
        if (changePosition(position_.x + mv_x, position_.y + mv_y, map->getMap(), bg))
            cur_sprite_ = sprite_[2 + animation];
    }
    if ((keys[SDL_SCANCODE_DOWN] || prec_key == SDL_SCANCODE_DOWN || key_buffer_[SDL_SCANCODE_DOWN]) &&
        map->getMap()[coinY[0] + 1][coinX[0]] != Tile::Wall) {
        prec_key = SDL_SCANCODE_DOWN;
        key_buffer_[SDL_SCANCODE_DOWN] = false;
        mv_y = speed;
        position_.x = coinX[0] * tailleCaseX;
        if (changePosition(position_.x + mv_x, position_.y + mv_y, map->getMap(), bg))
            cur_sprite_ = sprite_[4 + animation];
    }
    if ((keys[SDL_SCANCODE_UP] || prec_key == SDL_SCANCODE_UP || key_buffer_[SDL_SCANCODE_UP]) &&
        map->getMap()[coinY[1] - 1][coinX[0]] != Tile::Wall) {
        prec_key = SDL_SCANCODE_UP;
        key_buffer_[SDL_SCANCODE_UP] = false;
        mv_y = -speed;
        position_.x = coinX[0] * tailleCaseX;
        if (changePosition(position_.x + mv_x, position_.y + mv_y, map->getMap(), bg))
            cur_sprite_ = sprite_[6 + animation];
    }
}

void ThePacman::die(SDL_Surface *plancheSprites, SDL_Rect &src_bg, SDL_Surface *win_surf, SDL_Rect &bg, SDL_Window *pWindow) {

    int x{position_.x};

    for (int i{0}; i < 11; i++) { // animation

        if (i == 9) { // 9th sprite requires a different width than the others
            position_.w = 4;
            position_.x += 10;
        } else if (i > 9) {
            position_.w = 32;
            position_.x = x;
        }

        SDL_SetColorKey(plancheSprites, false, 0);
        SDL_BlitScaled(plancheSprites, &src_bg, win_surf, &bg);
        SDL_BlitScaled(plancheSprites, &die_animation_[i], win_surf, &position_);
        SDL_UpdateWindowSurface(pWindow);
        SDL_Delay(150);
    }

    SDL_UpdateWindowSurface(pWindow);

    lives_--;
}