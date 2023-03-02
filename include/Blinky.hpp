#ifndef BLINKY_HPP
#define BLINKY_HPP

#include "Ghost.hpp"

/* rouge */
class Blinky : public Ghost{
    private:
    public:
        Blinky(int PixelX, int PixelY);

        void move(int animation,SDL_Rect *PacPosition, std::vector<std::vector<Tile>> map, SDL_Rect bg);

};


#endif