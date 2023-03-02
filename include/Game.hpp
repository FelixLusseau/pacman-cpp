#ifndef GAME_HPP
#define GAME_HPP

#include "../include/BlankGhost.hpp"
#include "../include/Blinky.hpp"
#include "../include/BlueGhost.hpp"
#include "../include/Clyde.hpp"
#include "../include/Dot.hpp"
#include "../include/Eyes.hpp"
#include "../include/Inky.hpp"
#include "../include/Map.hpp"
#include "../include/Pinky.hpp"
#include "../include/ThePacman.hpp"
#include "../include/Write.hpp"
#include <SDL.h>
#include <iostream>

class Game {
  protected:
    Blinky *ghosts[1];
    ThePacman *pacman;
    Ghost *blueghost;
    Ghost *blankghost;
    Ghost *eyes;

    Map *map;
    Write *dictionary;
    std::vector<Dot *> dots;

    SDL_Window *pWindow;
    SDL_Surface *win_surf;
    SDL_Surface *plancheSprites;
    SDL_Rect src_bg; // x,y, w,h (0,0) en haut a gauche
    SDL_Rect src_bg_dotless;
    SDL_Rect src_bg_white;
    SDL_Rect bg; // ici scale x4

    int count;
    int score;

  public:
    Game();

    void draw();
    int start();

    /* renvoit 1 ou 0 pour determiner l'animation des sprites */
    int changeSprite(void);

    bool gameOver(void);
};

#endif