#include "../include/Character.hpp"
#include "../include/Map.hpp"

extern int mv_x, mv_y;
extern SDL_Scancode prec_key;

Character::Character(){};

void Character::changePosition(int x, int y, std::vector<std::vector<Tile>> map, SDL_Rect bg) {

    // tailles d'une case de la carte
    float tailleCaseX = float(bg.w) / float(map[0].size());
    float tailleCaseY = float(bg.h) / float(map.size());

    // taille de la case de pacman
    int tailleSprite = (position_.w / 2);

    // origine = centre de la case de pacman et pas son coin gauche
    int origineX = position_.x + tailleSprite;
    int origineY = position_.y + tailleSprite;

    int ligne = origineX / tailleCaseX;
    int colonne = origineY / tailleCaseY;

    // std::cout<<"vector: "<<ligne<<" "<<colonne<<" "<<std::endl;

    // origine futur
    int futurX = x + tailleSprite;
    int futurY = y + tailleSprite;

    if ((futurX < origineX && map[futurY / tailleCaseY][(futurX - tailleSprite) / tailleCaseX] == Tile::Wall) ||
        (futurY < origineY && map[(futurY - tailleSprite) / tailleCaseY][futurX / tailleCaseX] == Tile::Wall) ||
        (futurY > origineY && map[(futurY + tailleSprite) / tailleCaseY][(futurX) / tailleCaseX] == Tile::Wall) ||
        (futurX > origineX && map[(futurY) / tailleCaseY][(futurX + tailleSprite) / tailleCaseX] == Tile::Wall)) {
        mv_x = 0;
        mv_y = 0;
        prec_key = SDL_SCANCODE_UNKNOWN;
        return;
    }
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

    position_.x = x;
    position_.y = y;
}