#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include "Map.hpp"
#include <SDL.h>
#include <iostream>
#include <vector>

class Character {
  protected:
    /* sprite pour bouger dans les 4 directions (2 images par directions)
    right-left-down-up */
    SDL_Rect sprite_[8];

    /* sprite actuellement dessiné */
    SDL_Rect cur_sprite_;

    /* position dans la fenètre de jeu */
    SDL_Rect position_;

    SDL_Rect init_position_;

    /* dernière touche du clavier pressé (pacman) / direction prise (ghost)*/
    SDL_Scancode prec_key;

    /* vitesse du personnage */
    int speed;

    /* données de la carte: hauteur et longueur d'une case*/
    int height;
    int width;

  public:
    Character();
    Character(int px, int py);

    inline SDL_Rect *getSprite(int i) { return &sprite_[i]; };

    inline SDL_Rect *getPosition() { return &position_; };

    inline void setPosition(SDL_Rect newPosition) { position_ = newPosition; };

    inline SDL_Rect *get_currSprite() { return &cur_sprite_; };

    inline SDL_Scancode get_key() { return prec_key; };
    
    inline void set_speed(int newSpeed) { speed = newSpeed; };

    void changePosition(int x, int y, std::vector<std::vector<Tile>> map, SDL_Rect bg);
    inline SDL_Rect *get_initPosition() { return &init_position_; };
};

#endif