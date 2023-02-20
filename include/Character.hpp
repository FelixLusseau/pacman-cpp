#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include <SDL.h>
#include <iostream>
#include <vector>
#include "Map.hpp"

class Character{
    protected:
        /* sprite pour bouger dans les 4 directions (2 images par directions)
        right-left-down-up */
        SDL_Rect sprite_[8];

        /* sprite actuellement dessiné */
        SDL_Rect cur_sprite_;

        /* position dans la fenètre de jeu */
        SDL_Rect position_;
        
    public:
        Character();

        inline SDL_Rect* getSprite(int i){
            return &sprite_[i];
        };
        inline SDL_Rect* getPosition(){
            return &position_;
        };
        inline SDL_Rect* get_currSprite(){
            return &cur_sprite_;
        };

        void changePosition(int x, int y, std::vector<std::vector<Tile>> map);

};

#endif