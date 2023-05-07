#ifndef CLYDE_HPP
#define CLYDE_HPP

#include "Ghost.hpp"
#include <memory>

/* Orange ghost */
class Clyde : public Ghost {
  public:
    Clyde(const int PixelX, const int PixelY);

    void chase(const std::unique_ptr<ThePacman> &pacman, const std::vector<std::vector<Tile>> &map, const SDL_Rect bg) override;
};

#endif