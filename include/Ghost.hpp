#ifndef GHOST_HPP
#define GHOST_HPP

#include "Character.hpp"

class Ghost : public Character{
    protected:
    
    public:
        Ghost();

        void dontStopMoving(int animation,std::vector<std::vector<Tile>> map,SDL_Rect bg);
};


#endif