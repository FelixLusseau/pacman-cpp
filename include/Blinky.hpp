#ifndef BLINKY_HPP
#define BLINKY_HPP

#include "Ghost.hpp"
#include <memory>

/* rouge */
class Blinky : public Ghost {
  private:
  public:
    Blinky(int PixelX, int PixelY);

    void chase(std::unique_ptr<ThePacman> &pacman, std::vector<std::vector<Tile>> &map, SDL_Rect bg) override;
};

#endif