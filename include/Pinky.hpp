#ifndef PINKY_HPP
#define PINKY_HPP

#include "Ghost.hpp"
#include <memory>

/* rouge */
class Pinky : public Ghost {
  private:
  public:
    Pinky(const int PixelX, const int PixelY);

    void chase(const std::unique_ptr<ThePacman> &pacman, const std::vector<std::vector<Tile>> &map, const SDL_Rect bg) override;
};

#endif