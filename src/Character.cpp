#include "../include/Character.hpp"
#include "../include/Map.hpp"

Character::Character() {
    prec_key = SDL_SCANCODE_UNKNOWN;
    speed = 1;
};

Character::Character(const int px, const int py) {
    prec_key = SDL_SCANCODE_UNKNOWN;
    speed = 1;

    height = py;
    width = px;
};

Character::~Character() {}

inline bool operator==(const SDL_Rect &a, const SDL_Rect &b) { return a.x == b.x && a.y == b.y && a.w == b.w && a.h == b.h; }

int Character::changePosition(const int x, const int y, const std::vector<std::vector<Tile>> &map, const SDL_Rect bg) {

    // size of a tile
    float tailleCaseX{static_cast<float>(bg.w) / static_cast<float>(map[0].size())};
    float tailleCaseY{static_cast<float>(bg.h) / static_cast<float>(map.size())};

    // size of the Pacman tile
    int halfWidth = (position_.w / 2);

    // origin = center of the Pacman and not the top left corner
    int origineX{position_.x + halfWidth};
    int origineY{position_.y + halfWidth};

    // futur origin
    int futurX{x + halfWidth};
    int futurY{y + halfWidth};

    // teleportation tunnel
    if ((futurX < origineX && map[futurY / tailleCaseY][(futurX - halfWidth) / tailleCaseX] == Tile::EscapeTunnel)) {
        position_.x = x + 19 * tailleCaseX;
        position_.y = y;

        return 0;
    }
    if ((futurX > origineX && map[futurY / tailleCaseY][(futurX + halfWidth) / tailleCaseX] == Tile::EscapeTunnel)) {
        position_.x = x - 19 * tailleCaseX;
        position_.y = y;
        return 0;
    }

    // Corridors
    // if (futurX < origineX && map[futurY / tailleCaseY][(futurX - halfWidth) / tailleCaseX] == Tile::Corridor)
    //     speed = speed / 2;

    // if (futurX > origineX && map[futurY / tailleCaseY][(futurX + halfWidth) / tailleCaseX] == Tile::Corridor)
    //     speed = speed / 2;

    // collision wall
    if ((futurX < origineX && map[futurY / tailleCaseY][(futurX - halfWidth) / tailleCaseX] == Tile::Wall) ||
        (futurY < origineY && map[(futurY - halfWidth) / tailleCaseY][futurX / tailleCaseX] == Tile::Wall) ||
        (futurY > origineY && map[(futurY + halfWidth) / tailleCaseY][(futurX) / tailleCaseX] == Tile::Wall) ||
        (futurX > origineX && map[(futurY) / tailleCaseY][(futurX + halfWidth) / tailleCaseX] == Tile::Wall)) {

        prec_key = SDL_SCANCODE_UNKNOWN;
        return 0;
    }

    // ghost house door collision
    float pixelX{static_cast<float>(bg.w) / static_cast<float>(map[0].size())};
    float pixelY{static_cast<float>(bg.h) / static_cast<float>(map.size())};

    int pX{static_cast<int>(pixelX)};
    int pY{static_cast<int>(pixelY)};

    SDL_Rect initial_pacman_position = {10 * pX, 20 * pY, 32, 32};

    // collision with the ghost house door for Pacman
    if ((futurX < origineX && map[futurY / tailleCaseY][(futurX - halfWidth) / tailleCaseX] == Tile::GhostHouseDoor &&
         init_position_ == initial_pacman_position) ||
        (futurY < origineY && map[(futurY - halfWidth) / tailleCaseY][futurX / tailleCaseX] == Tile::GhostHouseDoor &&
         init_position_ == initial_pacman_position) ||
        (futurY > origineY && map[(futurY + halfWidth) / tailleCaseY][(futurX) / tailleCaseX] == Tile::GhostHouseDoor &&
         init_position_ == initial_pacman_position) ||
        (futurX > origineX && map[(futurY) / tailleCaseY][(futurX + halfWidth) / tailleCaseX] == Tile::GhostHouseDoor &&
         init_position_ == initial_pacman_position)) {

        prec_key = SDL_SCANCODE_UNKNOWN;
        return 0;
    }

    // collision at the corners with a sprite having a certain roundness
    int rondeur{3};
    if ((map[(y + rondeur) / tailleCaseY][(x + rondeur) / tailleCaseX] == Tile::Wall) ||
        map[(y + rondeur) / tailleCaseY][(x + position_.h - rondeur) / tailleCaseX] == Tile::Wall ||
        map[(y + position_.w - rondeur) / tailleCaseY][(x + rondeur) / tailleCaseX] == Tile::Wall ||
        map[(y + position_.w - rondeur) / tailleCaseY][(x + position_.h - rondeur) / tailleCaseX] == Tile::Wall) {
        prec_key = SDL_SCANCODE_UNKNOWN;
        return 0;
    }

    position_.x = x;
    position_.y = y;
    return 1;
}
