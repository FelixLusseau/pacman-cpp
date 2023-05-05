#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include "Map.hpp"
#include <SDL.h>
#include <array>
#include <iostream>
#include <vector>

#include <ctime>
#include <memory>

class Character {
  protected:
    /* sprite pour bouger dans les 4 directions (2 images par directions)
       ordre: right-left-down-up */
    std::array<SDL_Rect, 8> sprite_;

    /* sprite actuellement dessiné */
    SDL_Rect cur_sprite_;

    /* position dans la fenètre de jeu */
    SDL_Rect position_;

    /*position initial */
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
    virtual ~Character();

    inline SDL_Rect *getSprite(int i) { return &sprite_[i]; };

    inline SDL_Rect *getPosition() { return &position_; };

    inline void setPosition(SDL_Rect newPosition) { position_ = newPosition; };

    /* sprite actuel */
    inline SDL_Rect *get_currSprite() { return &cur_sprite_; };

    /* renvoit la dernière touche du clavier pressé = direction*/
    inline SDL_Scancode get_key() { return prec_key; };

    inline void set_speed(int newSpeed) { speed = newSpeed; };

    int changePosition(int x, int y, std::vector<std::vector<Tile>> &map, SDL_Rect bg);

    inline SDL_Rect *get_initPosition() { return &init_position_; };

    /*méthode de mouvement */
    virtual void move(const Uint8 *keys, int animation, std::unique_ptr<Map> &map, SDL_Rect bg) = 0;
};

#endif