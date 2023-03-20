#include "../include/Character.hpp"
#include "../include/Map.hpp"

Character::Character() {
    prec_key = SDL_SCANCODE_UNKNOWN;
    speed = 1;
};

Character::Character(int px, int py) {
    prec_key = SDL_SCANCODE_UNKNOWN;
    speed = 1;

    height=py;
    width=px;

};

void Character::changePosition(int x, int y, std::vector<std::vector<Tile>> map, SDL_Rect bg) {

    // tailles d'une case de la carte
    float tailleCaseX = float(bg.w) / float(map[0].size());
    float tailleCaseY = float(bg.h) / float(map.size());

    // taille de la case de pacman
    int halfWidth = (position_.w / 2);

    // origine = centre de la case de pacman et pas son coin gauche
    int origineX = position_.x + halfWidth;
    int origineY = position_.y + halfWidth;

    // origine futur
    int futurX = x + halfWidth;
    int futurY = y + halfWidth;

    // tunnel de téléportation
    if ((futurX < origineX && map[futurY / tailleCaseY][(futurX - halfWidth) / tailleCaseX] == Tile::EscapeTunnel)) {
        position_.x = x + 19 * tailleCaseX;
        position_.y = y;

        return;
    }
    if ((futurX > origineX && map[futurY / tailleCaseY][(futurX + halfWidth) / tailleCaseX] == Tile::EscapeTunnel)) {
        position_.x = x - 19 * tailleCaseX;
        position_.y = y;
        return;
    }

    // collision mur
    if ((futurX < origineX && map[futurY / tailleCaseY][(futurX - halfWidth) / tailleCaseX] == Tile::Wall) ||
        (futurY < origineY && map[(futurY - halfWidth) / tailleCaseY][futurX / tailleCaseX] == Tile::Wall) ||
        (futurY > origineY && map[(futurY + halfWidth) / tailleCaseY][(futurX) / tailleCaseX] == Tile::Wall) ||
        (futurX > origineX && map[(futurY) / tailleCaseY][(futurX + halfWidth) / tailleCaseX] == Tile::Wall)) {
        
        prec_key = SDL_SCANCODE_UNKNOWN;
        return;
    }

    // collision aux coins avec un sprite ayant une certaine rondeur
    int rondeur{6};
    if ((map[(y + rondeur) / tailleCaseY][(x + rondeur) / tailleCaseX] == Tile::Wall) ||
        map[(y + rondeur) / tailleCaseY][(x + position_.h - rondeur) / tailleCaseX] == Tile::Wall ||
        map[(y + position_.w - rondeur) / tailleCaseY][(x + rondeur) / tailleCaseX] == Tile::Wall ||
        map[(y + position_.w - rondeur) / tailleCaseY][(x + position_.h - rondeur) / tailleCaseX] == Tile::Wall) {
        prec_key = SDL_SCANCODE_UNKNOWN;
        return;
    }

    position_.x = x;
    position_.y = y;
}
