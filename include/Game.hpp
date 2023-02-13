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
        SDL_Rect src_bg ;   // x,y, w,h (0,0) en haut a gauche
        SDL_Rect bg ;       // ici scale x4

        int count;

    public:
        Game();

        void draw();
        int start();

};

#endif