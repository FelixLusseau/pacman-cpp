#ifndef CLYDE_HPP
#define CLYDE_HPP

#include "Ghost.hpp"

/* rouge */
class Clyde : public Ghost {
  private:
  public:
    Clyde();
    void chase(int animation,ThePacman *pacman, std::vector<std::vector<Tile>> map, SDL_Rect bg) override;
};

#endif