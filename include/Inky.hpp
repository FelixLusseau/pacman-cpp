#ifndef INKY_HPP
#define INKY_HPP

#include "Ghost.hpp"
#include <memory>

/* Blue ghost */
class Inky : public Ghost {
  private:
    // Inky uses Blinky's position to calculate his target for the chase
    std::shared_ptr<Ghost> blinky_;

  public:
    Inky(const int PixelX, const int PixelY);
    Inky(const int PixelX, const int PixelY, std::shared_ptr<Ghost> blinky);

    void chase(const std::unique_ptr<ThePacman> &pacman, const std::vector<std::vector<Tile>> &map, const SDL_Rect bg) override;
};

#endif