#ifndef BLINKY_HPP
#define BLINKY_HPP

#include "Ghost.hpp"

/* rouge */
class Blinky : public Ghost{
    private:
    public:
        Blinky(int PixelX, int PixelY);

        void chase(int animation,ThePacman *pacman, std::vector<std::vector<Tile>> map, SDL_Rect bg) override;

};


#endif