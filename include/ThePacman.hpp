#ifndef THEPACMAN_HPP
#define THEPACMAN_HPP

#include "../include/Character.hpp"
#include <array>
#include <iostream>
#include <vector>

class ThePacman : public Character {
  private:
    std::array<SDL_Rect, 11> die_animation;
    int lives_;                                            // number of lives of Pacman
    std::array<bool, SDL_NUM_SCANCODES> key_buffer{false}; // Buffer of pressed keys

  public:
    ThePacman(const int x, const int y);

    /**
     * @brief Function to move Pacman
     *
     * @param keys
     * @param animation
     * @param map
     * @param bg
     */
    void move(const Uint8 *keys, const int animation, const std::unique_ptr<Map> &map, const SDL_Rect bg);

    /**
     * @brief Animation for the death of Pacman
     *
     * @param plancheSprites
     * @param src_bg
     * @param win_surf
     * @param bg
     * @param pWindow
     */
    void die(SDL_Surface *plancheSprites, SDL_Rect &src_bg, SDL_Surface *win_surf, SDL_Rect &bg, SDL_Window *pWindow);

    /**
     * @brief Get the lives of Pacman
     *
     * @return int
     */
    inline int getLives() const { return lives_; }
};

#endif