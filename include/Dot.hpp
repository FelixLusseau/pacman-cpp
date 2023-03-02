#ifndef DOT_HPP
#define DOT_HPP

#include <iostream>
#include <vector>
#include <SDL.h>


enum class TypeDot { Simple, Big, Fruit };

class Dot {
    private:

    TypeDot type;

    /* combien de point il vaut */
    int point;
    bool exist;

    SDL_Rect sprite_;

    /* position dans la fenètre de jeu */
    SDL_Rect position_;
    
    public:

    Dot(int x, int y, TypeDot type);

    bool inline getExist(void){
        return exist;
    }
    inline SDL_Rect* getPosition(void){
        return &position_;
    }
    inline SDL_Rect* getSprite(void){
        return &sprite_;
    } 
    inline int getPoint(void){
        return point;
    }

    /* fonction pour manger les points: renvoit 0 si pas mangé, son nombre de point sinon */
    int getEat(SDL_Rect*pac_position);

};

#endif