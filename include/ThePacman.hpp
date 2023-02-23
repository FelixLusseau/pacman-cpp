#ifndef THEPACMAN_HPP
#define THEPACMAN_HPP

#include <iostream>
#include "../include/Character.hpp"
#include <iostream>
#include <vector>

class ThePacman : public Character{
    private:

    SDL_Rect die_animation[11];
    
    public:

    ThePacman();

    /* pacman bouge */
    void move(const Uint8 *keys, int animation, std::vector<std::vector<Tile>> map, SDL_Rect bg);

    /* pacman meurt */
    void die(SDL_Surface *plancheSprites,SDL_Rect *src_bg,SDL_Surface *win_surf,SDL_Rect *bg,SDL_Window *pWindow);

};

#endif