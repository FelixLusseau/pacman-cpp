#ifndef CLYDE_HPP
#define CLYDE_HPP

#include "Ghost.hpp"
#include <memory>

/* rouge */
class Clyde : public Ghost {
  private:
  public:
    Clyde(int PixelX, int PixelY);
    void chase(const std::unique_ptr<ThePacman> &pacman, const std::vector<std::vector<Tile>> &map, const SDL_Rect bg) override;
};

#endif