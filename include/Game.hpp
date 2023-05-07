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
#include <SDL2/SDL.h>
#include <array>
#include <ctime>
#include <iostream>
#include <memory>

class Game {
  private:
    std::array<std::shared_ptr<Ghost>, 4> ghosts_;
    std::shared_ptr<Ghost> blinky_;
    std::shared_ptr<Ghost> pinky_;
    std::shared_ptr<Ghost> inky_;
    std::shared_ptr<Ghost> clyde_;
    std::unique_ptr<ThePacman> pacman_;

    std::unique_ptr<Map> map_;
    std::unique_ptr<Write> dictionary_;
    std::vector<std::unique_ptr<Dot>> dots_;
    std::unique_ptr<Bonus> bonus_;

    SDL_Window *pWindow;
    SDL_Surface *win_surf;
    SDL_Surface *plancheSprites;
    SDL_Rect src_bg; // x,y, w,h (0,0) at top-left
    SDL_Rect src_bg_dotless;
    SDL_Rect src_bg_white;
    SDL_Rect bg; // scale x4

    int count_;
    int score_;
    bool launched_;

  public:
    Game();
    static int ghosts_eaten, level;
    static bool next_level;
    static clock_t timer_begin, timer_end;

    /**
     * @brief Main display function of the game
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
    void resetPositions(std::array<std::shared_ptr<Ghost>, 4> &ghosts, std::unique_ptr<ThePacman> &pacman);

    /**
     * @brief Change the level of the game
     *
     * @param ghosts
     * @param pacman
     * @param bg
     */
    void nextLevel(std::array<std::shared_ptr<Ghost>, 4> &ghosts, std::unique_ptr<ThePacman> &pacman, SDL_Rect bg);

    /**
     * @brief An animation between level 2 and 3.
     * Pacman is chased by a ghost and then the affaid
     * ghost is chased by a big Pacman
     *
     */
    void level2To3();
};

#endif