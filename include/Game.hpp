#ifndef GAME_HPP
#define GAME_HPP

#include "../include/Blinky.hpp"
#include "../include/Bonus.hpp"
#include "../include/Clyde.hpp"
#include "../include/Dot.hpp"
#include "../include/Inky.hpp"
#include "../include/Map.hpp"
#include "../include/Pinky.hpp"
#include "../include/ThePacman.hpp"
#include "../include/Write.hpp"
#include <SDL.h>
#include <array>
#include <ctime>
#include <iostream>

class Game {
  protected:
    Ghost *ghosts[4];
    ThePacman *pacman;

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
    bool launched;

    Bonus *bonus;

  public:
    Game();
    static int ghosts_eaten, level;
    static bool next_level;

    void draw();
    int start();

    /* renvoit 1 ou 0 pour determiner l'animation des sprites */
    int changeSprite(void);

    static clock_t timer_begin, timer_end;
    bool gameOver(void);
    void resetPositions(Ghost **ghosts, ThePacman *pacman, std::vector<std::vector<Tile>> map, SDL_Rect bg);
    void nextLevel(Ghost **ghosts, ThePacman *pacman, std::vector<std::vector<Tile>> map, SDL_Rect bg);

    void level2To3();
};

#endif