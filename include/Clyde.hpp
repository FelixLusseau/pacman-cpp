#ifndef CLYDE_HPP
#define CLYDE_HPP

#include "Ghost.hpp"
#include <memory>

/* rouge */
class Clyde : public Ghost {
  private:
  public:
    Clyde(int PixelX, int PixelY);
    void chase( std::unique_ptr<ThePacman> &pacman, std::vector<std::vector<Tile>> map, SDL_Rect bg) override;
};

#endif