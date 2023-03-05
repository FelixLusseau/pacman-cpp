#ifndef INKY_HPP
#define INKY_HPP

#include "Ghost.hpp"

/* rouge */
class Inky : public Ghost {
  private:
  public:
    Inky();
    void chase(int animation,ThePacman *pacman, std::vector<std::vector<Tile>> map, SDL_Rect bg) override;
};

#endif