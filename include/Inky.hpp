#ifndef INKY_HPP
#define INKY_HPP

#include "Ghost.hpp"

/* rouge */
class Inky : public Ghost {
  private:
    Ghost *blinky_;
  public:
    Inky(int PixelX, int PixelY);
    Inky(int PixelX, int PixelY, Ghost *blinky);
    
    void chase(int animation,ThePacman *pacman, std::vector<std::vector<Tile>> map, SDL_Rect bg) override;
};

#endif