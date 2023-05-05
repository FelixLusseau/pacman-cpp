#ifndef THEPACMAN_HPP
#define THEPACMAN_HPP

#include "../include/Character.hpp"
#include <array>
#include <iostream>
#include <vector>

class ThePacman : public Character {
  private:
    std::array<SDL_Rect, 11> die_animation;
    int lives_; // nombre de vies

  public:
    ThePacman(int x, int y);

    /* pacman bouge */
    void move(const Uint8 *keys, int animation, std::unique_ptr<Map> &map, SDL_Rect bg);

    /* pacman meurt */
    void die(SDL_Surface *plancheSprites, SDL_Rect *src_bg, SDL_Surface *win_surf, SDL_Rect *bg, SDL_Window *pWindow);

    inline int getLives() const { return lives_; }
};

#endif