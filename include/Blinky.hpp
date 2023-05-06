#ifndef BLINKY_HPP
#define BLINKY_HPP

#include "Ghost.hpp"
#include <memory>

/* Red ghost */
class Blinky : public Ghost {
  public:
    Blinky(const int PixelX, const int PixelY);

    void chase(const std::unique_ptr<ThePacman> &pacman, const std::vector<std::vector<Tile>> &map, const SDL_Rect bg) override;
};

#endif