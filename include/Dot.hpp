#ifndef DOT_HPP
#define DOT_HPP

#include <iostream>
#include <vector>
#include <SDL.h>

class Dot {
    private:

    /* combien de point il vaut */
    int point;
    bool exist;

    SDL_Rect sprite_;

    /* position dans la fenètre de jeu */
    SDL_Rect position_;
    
    public:

    Dot(int x, int y);

    bool inline getExist(void){
        return exist;
    }
    inline SDL_Rect* getPosition(void){
        return &position_;
    }
    inline SDL_Rect* getSprite(void){
        return &sprite_;
    }

};

#endif