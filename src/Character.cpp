#include "../include/Character.hpp"
#include "../include/Map.hpp"

extern SDL_Scancode prec_key;

Character::Character() { SDL_Scancode prec_key = SDL_SCANCODE_UNKNOWN; };

void Character::changePosition(int x, int y, std::vector<std::vector<Tile>> map, SDL_Rect bg) {

    // tailles d'une case de la carte
    float tailleCaseX = float(bg.w) / float(map[0].size());
    float tailleCaseY = float(bg.h) / float(map.size());

    // taille de la case de pacman
    int tailleSprite = (position_.w / 2);

    // origine = centre de la case de pacman et pas son coin gauche
    int origineX = position_.x + tailleSprite;
    int origineY = position_.y + tailleSprite;

    // origine futur
    int futurX = x + tailleSprite;
    int futurY = y + tailleSprite;

    // tunnel de téléportation
    if ((futurX < origineX && map[futurY / tailleCaseY][(futurX - tailleSprite) / tailleCaseX] == Tile::EscapeTunnel)) {
        position_.x = x + 19 * tailleCaseX;
        position_.y = y;
        return;
    }
    if ((futurX > origineX && map[futurY / tailleCaseY][(futurX + tailleSprite) / tailleCaseX] == Tile::EscapeTunnel)) {
        position_.x = x - 19 * tailleCaseX;
        position_.y = y;
        return;
    }

    // collision mur
    if ((futurX < origineX && map[futurY / tailleCaseY][(futurX - tailleSprite) / tailleCaseX] == Tile::Wall) ||
        (futurY < origineY && map[(futurY - tailleSprite) / tailleCaseY][futurX / tailleCaseX] == Tile::Wall) ||
        (futurY > origineY && map[(futurY + tailleSprite) / tailleCaseY][(futurX) / tailleCaseX] == Tile::Wall) ||
        (futurX > origineX && map[(futurY) / tailleCaseY][(futurX + tailleSprite) / tailleCaseX] == Tile::Wall)) {

        prec_key = SDL_SCANCODE_UNKNOWN;
        return;
    }

    // collision aux coins
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