#ifndef PINKY_HPP
#define PINKY_HPP

#include "Ghost.hpp"

/* rouge */
class Pinky : public Ghost {
  private:
  public:
    Pinky(int PixelX, int PixelY);

    void chase(int animation,ThePacman *pacman, std::vector<std::vector<Tile>> map, SDL_Rect bg) override;
};

#endif