#ifndef INKY_HPP
#define INKY_HPP

#include "Ghost.hpp"
#include <memory>

/* rouge */
class Inky : public Ghost {
  private:
    /* inky utlise la position de blinky pour sa stratégie de chasse*/
    // std::unique_ptr<Ghost> blinky_;
    Ghost *blinky_;

  public:
    Inky(const int PixelX, const int PixelY);
    Inky(const int PixelX, const int PixelY, Ghost *blinky);

    void chase(const std::unique_ptr<ThePacman> &pacman, const std::vector<std::vector<Tile>> &map, const SDL_Rect bg) override;
};

#endif