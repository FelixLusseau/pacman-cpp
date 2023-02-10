#ifndef THEPACMAN_HPP
#define THEPACMAN_HPP

#include <SDL.h>
#include <iostream>

class thePacman{
    private:
    SDL_Rect sprite_r[2];
    SDL_Rect sprite_l[2];
    SDL_Rect sprite_d[2];
    SDL_Rect sprite_u[2];

    SDL_Rect position;

    public:

    thePacman();

    inline SDL_Rect* getRight(int oneORtwo){
        return &sprite_r[oneORtwo];
    }
    inline SDL_Rect* getLeft(int oneORtwo){
        return &sprite_l[oneORtwo];
    }
    inline SDL_Rect* getDown(int oneORtwo){
        return &sprite_d[oneORtwo];
    }
    inline SDL_Rect* getUp(int oneORtwo){
        return &sprite_u[oneORtwo];
    }
    inline SDL_Rect* getPosition(){
        return &position;
    }

};

#endif