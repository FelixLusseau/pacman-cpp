#include "../include/Character.hpp"
#include "../include/Map.hpp"

Character::Character(){};

void Character::changePosition(int x, int y, std::vector<std::vector<Tile>> map) {
    int ligne=position_.x%34;
    int colonne=position_.y%34;

    if( x<=168*4 && x>=0 && y<=216*4 && y>=0){
        position_.x = x;
        position_.y = y;
    }
    


}