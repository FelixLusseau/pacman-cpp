#ifndef GAME_HPP
#define GAME_HPP

#include <SDL.h>
#include <iostream>
#include "ThePacman.hpp"
#include "Blinky.hpp"

class Game{
    protected:
        Ghost *ghosts[4];
        ThePacman *pacman;

        SDL_Window *pWindow;
        SDL_Surface *win_surf;
        SDL_Surface *plancheSprites;

        int count;

    public:
        Game();
        int start();
        void draw();


};

#endif