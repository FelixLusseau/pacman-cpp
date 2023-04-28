#ifndef BONUS_HPP
#define BONUS_HPP

#include <SDL.h>

enum class TypeBonus { Cherry, Strawberry, Orange, Apple, Melon, Galaxian, Bell, Key };

class Bonus {
  private:
    TypeBonus type;
    int point;
    bool exist;
    SDL_Rect sprite_;
    SDL_Rect position_;

  public:
    Bonus();
};

#endif