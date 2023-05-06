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
#include <memory>

class Game {
  protected:
    Ghost *ghosts[4];
    std::unique_ptr<ThePacman> pacman;

    std::unique_ptr<Map> map;
    std::unique_ptr<Write> dictionary;
    std::vector<std::unique_ptr<Dot>> dots;

    SDL_Window *pWindow;
    SDL_Surface *win_surf;
    SDL_Surface *plancheSprites;
    SDL_Rect src_bg; // x,y, w,h (0,0) at top-left
    SDL_Rect src_bg_dotless;
    SDL_Rect src_bg_white;
    SDL_Rect bg; // scale x4

    int count;
    int score;
    bool launched;

    std::unique_ptr<Bonus> bonus;

  public:
    Game();
    static int ghosts_eaten, level;
    static bool next_level;

    /**
     * @brief Display of the game
     *
     */
    void draw();

    /**
     * @brief Main function of the game
     *
     */
    int start();

    /**
     * @brief Calculate the sprite in the array of sprites to display for the animation
     *
     * @return int
     */
    int changeSprite(void);

    static clock_t timer_begin, timer_end;

    /**
     * @brief Function executed when Pacman dies
     *
     * @return true
     * @return false
     */
    bool gameOver(void);

    /**
     * @brief Reset the position of the ghosts and Pacman in case of death or level change
     *
     * @param ghosts
     * @param pacman
     */
    void resetPositions(Ghost **ghosts, std::unique_ptr<ThePacman> &pacman);

    /**
     * @brief Change the level of the game
     *
     * @param ghosts
     * @param pacman
     * @param bg
     */
    void nextLevel(Ghost **ghosts, std::unique_ptr<ThePacman> &pacman, SDL_Rect bg);

    /**
     * @brief An animation between level 2 and 3
     *
     */
    void level2To3();
};

#endif