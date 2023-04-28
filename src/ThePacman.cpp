#include "../include/ThePacman.hpp"

ThePacman::ThePacman(int x, int y) : Character() {
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

void ThePacman::move(const Uint8 *keys, int animation, std::vector<std::vector<Tile>> map, SDL_Rect bg) {


    // tailles d'une case de la carte
    float tailleCaseX{float(bg.w) / float(map[0].size())};
    float tailleCaseY{float(bg.h) / float(map.size())};

    // collision aux coins avec un sprite ayant une certaine rondeur
    int rondeur{6};

    // coordonnées des coins du sprite
    int coinX[2]={(int)((position_.x+rondeur)/tailleCaseX), (int)((position_.x + position_.w-rondeur)/tailleCaseX)};
    int coinY[2]={(int)((position_.y+rondeur)/tailleCaseY), (int)((position_.y + position_.w-rondeur)/tailleCaseY)};

    SDL_Rect sp{cur_sprite_};

    int mv_x{0};
    int mv_y{0};

    if ((keys[SDL_SCANCODE_RIGHT] || prec_key == SDL_SCANCODE_RIGHT) && map[coinY[0]][coinX[0] + 1] != Tile::Wall) {
        prec_key = SDL_SCANCODE_RIGHT;
        mv_x = 2;
        if (changePosition(position_.x + mv_x, position_.y + mv_y, map, bg))
            cur_sprite_ = sprite_[0 + animation];
    }
    if ((keys[SDL_SCANCODE_LEFT] || prec_key == SDL_SCANCODE_LEFT) && map[coinY[0]][coinX[1] - 1] != Tile::Wall) {
        prec_key = SDL_SCANCODE_LEFT;
        mv_x = -2;
        if (changePosition(position_.x + mv_x, position_.y + mv_y, map, bg))
            cur_sprite_ = sprite_[2 + animation];
    }
    if ((keys[SDL_SCANCODE_DOWN] || prec_key == SDL_SCANCODE_DOWN) && map[coinY[0]+ 1][coinX[0]] != Tile::Wall) {
        prec_key = SDL_SCANCODE_DOWN;
        mv_y = 2;
        if (changePosition(position_.x + mv_x, position_.y + mv_y, map, bg))
            cur_sprite_ = sprite_[4 + animation];
    }
    if ((keys[SDL_SCANCODE_UP] || prec_key == SDL_SCANCODE_UP) && map[coinY[1] - 1][coinX[0]] != Tile::Wall) {
        prec_key = SDL_SCANCODE_UP;
        mv_y = -2;
        if (changePosition(position_.x + mv_x, position_.y + mv_y, map, bg))
            cur_sprite_ = sprite_[6 + animation];
    }
    
    // cur_sprite_=sp;
    // this->changePosition(position_.x + mv_x, position_.y + mv_y, map, bg);

    // std::cout<<position_.x<<" "<<position_.y<<std::endl;
}

void ThePacman::die(SDL_Surface *plancheSprites, SDL_Rect *src_bg, SDL_Surface *win_surf, SDL_Rect *bg, SDL_Window *pWindow) {

    int x{position_.x};
    int y{position_.y};

    for (int i{0}; i < 11; i++) { // animation

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

    lives_--;
}