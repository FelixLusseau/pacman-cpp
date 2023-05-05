#ifndef THEPACMAN_HPP
#define THEPACMAN_HPP

#include "../include/Character.hpp"
#include <iostream>
#include <vector>

class ThePacman : public Character {
  private:
    SDL_Rect die_animation[11];
    int lives_; // nombre de vies

  public:
    ThePacman(int x, int y);

    /* pacman bouge */
    void move(const Uint8 *keys, int animation,  Map *map, SDL_Rect bg);

    /* pacman meurt */
    void die(SDL_Surface *plancheSprites, SDL_Rect *src_bg, SDL_Surface *win_surf, SDL_Rect *bg, SDL_Window *pWindow);

    inline int getLives() { return lives_; }
};

#endif