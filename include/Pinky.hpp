#ifndef PINKY_HPP
#define PINKY_HPP

#include "Ghost.hpp"
#include <memory>

/* pink ghost */
class Pinky : public Ghost {
  public:
    Pinky(const int PixelX, const int PixelY);

    void chase(const std::unique_ptr<ThePacman> &pacman, const std::vector<std::vector<Tile>> &map, const SDL_Rect bg) override;
};

#endif