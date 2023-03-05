#ifndef GHOST_HPP
#define GHOST_HPP

#include "Character.hpp"
#include "ThePacman.hpp"

class Ghost : public Character{
    protected:
    
    public:
        Ghost();

        void dontStopMoving(int animation,std::vector<std::vector<Tile>> map,SDL_Rect bg);

        virtual void chase(int animation,ThePacman *pacman, std::vector<std::vector<Tile>> map, SDL_Rect bg) ;

        /* est bien placé à une intersection */
        bool intersection(float tailleCaseX,float tailleCaseY,std::vector<Tile> directions);

        /* change key_prec selon la meilleur direction pour aller au Goal au plus court */
        void shortestPath(SDL_Rect *Goal,std::vector<Tile> directions,std::vector<std::vector<Tile>> map, SDL_Rect bg);


};


#endif